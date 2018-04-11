#include "axismodewidget.h"

#include <QKeyEvent>
#include <QDebug>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QStyledItemDelegate>

AxisModeWidget::AxisModeWidget(quint16 axis,QWidget *parent) : QWidget(parent),
  m_keyCtlIsPress(false),
  m_axisNum(axis)
{
  QHBoxLayout *hlayout=new QHBoxLayout(this);
  setLayout(hlayout);
  m_checkBox=new QCheckBox(this);
  m_checkBox->setObjectName("modeCheckBox");
  m_comboBox=new QComboBox(this);
  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(m_comboBox);
  m_comboBox->setItemDelegate(itemDelegate);
  m_comboBox->setObjectName("modeComboBox");
  QStringList list;
  list<<tr("0IDLE")\
     <<tr("1ADC")\
     <<tr("2IPA")\
     <<tr("3MPI")\
     <<tr("4COL")\
     <<tr("5CCL")\
     <<tr("6VCL")\
     <<tr("7VPL")\
     <<tr("8VSL")\
     <<tr("9FIX")\
     <<tr("10PT")\
     <<tr("11DB")\
     <<tr("12CSC");
  m_comboBox->addItems(list);
  hlayout->addWidget(m_checkBox);
  hlayout->addWidget(m_comboBox);
  hlayout->setStretch(0,0);
  hlayout->setStretch(1,1);
  hlayout->setMargin(0);

  connect(m_checkBox,SIGNAL(clicked(bool)),this,SLOT(onCheckBoxClicked(bool)));
  connect(m_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxCurrentIndexChanged(int)));
}

AxisModeWidget::~AxisModeWidget()
{

}

bool AxisModeWidget::checked() const
{
  return m_checkBox->isChecked();
}

void AxisModeWidget::setChecked(bool checked)
{
  m_checkBox->setChecked(checked);
}

quint16 AxisModeWidget::axisNum() const
{
  return m_axisNum;
}

void AxisModeWidget::setAxisNum(const quint16 axisNum)
{
  m_axisNum = axisNum;
}

quint8 AxisModeWidget::mode() const
{
  return m_comboBox->currentIndex();
}

void AxisModeWidget::setMode(const quint8 mode)
{
  m_comboBox->setCurrentIndex(mode);
}

void AxisModeWidget::keyPressEvent(QKeyEvent *event)
{
  if(event->key()==Qt::Key_Control)
  {
    qDebug()<<"key press";
    m_keyCtlIsPress=true;
  }
  QWidget::keyPressEvent(event);
}

void AxisModeWidget::keyReleaseEvent(QKeyEvent *event)
{
  if(event->key()==Qt::Key_Control)
  {
    qDebug()<<"key release ";
    m_keyCtlIsPress=false;
  }
  QWidget::keyReleaseEvent(event);
}

void AxisModeWidget::onCheckBoxClicked(bool checked)
{
  Q_UNUSED(checked);

  if(!m_keyCtlIsPress)
    emit clearOthers(m_axisNum);
}

void AxisModeWidget::onComboBoxCurrentIndexChanged(int index)
{
  emit modeChanged(m_axisNum,index);
}

