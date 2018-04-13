#include "modectlpanel.h"

#include <QKeyEvent>
#include <QDebug>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QVBoxLayout>

UiCheckCombo::UiCheckCombo(quint16 axis,QWidget *parent):QWidget(parent),
  m_axisNum(axis)
{
  QHBoxLayout *hlayout=new QHBoxLayout(this);
  setLayout(hlayout);
  m_checkBox=new QCheckBox(this);
  m_checkBox->setObjectName("modeCheckBox");
  m_checkBox->setText(tr("Axis_%1").arg(axis+1));
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

  connect(m_checkBox,SIGNAL(clicked(bool)),this,SIGNAL(checkChanged(bool)));
  connect(m_comboBox,SIGNAL(currentIndexChanged(int)),this,SIGNAL(modeChanged(int)));
}


UiCheckCombo::~UiCheckCombo()
{

}

ModeCtlPanel::ModeCtlPanel(QWidget *parent):QWidget(parent),
  m_keyCtlIsPressed(false),
  m_axisCount(0)
{
  QVBoxLayout *vlayout=new QVBoxLayout(this);
  setLayout(vlayout);
}

ModeCtlPanel::ModeCtlPanel(quint16 axisCount,QWidget *parent) : QWidget(parent),
  m_axisCount(axisCount),
  m_keyCtlIsPressed(false)
{
  QVBoxLayout *vlayout=new QVBoxLayout(this);
  setLayout(vlayout);

  for(int i=0;i<axisCount;i++)
  {
    UiCheckCombo *uiBox=new UiCheckCombo(i,this);
    connect(uiBox,SIGNAL(checkChanged(bool)),this,SLOT(onCheckChanged(bool)));
    connect(uiBox,SIGNAL(modeChanged(int)),this,SLOT(onModeChanged(int)));
    m_uiCheckComboList.append(uiBox);
    vlayout->addWidget(uiBox);
  }
}

ModeCtlPanel::~ModeCtlPanel()
{

}

void ModeCtlPanel::setAxis(quint16 axis)
{
  m_axisCount=axis;
  clearUiCheckComboList();
  for(int i=0;i<axis;i++)
  {
    UiCheckCombo *uiBox=new UiCheckCombo(i,this);
    connect(uiBox,SIGNAL(checkChanged(bool)),this,SLOT(onCheckChanged(bool)));
    connect(uiBox,SIGNAL(modeChanged(int)),this,SLOT(onModeChanged(int)));
    m_uiCheckComboList.append(uiBox);
    layout()->addWidget(uiBox);
  }
}

bool ModeCtlPanel::isChecked(quint16 axis)
{
  return m_uiCheckComboList.at(axis)->m_checkBox->isChecked();
}

int ModeCtlPanel::mode(quint16 axis)
{
  return m_uiCheckComboList.at(axis)->m_comboBox->currentIndex();
}

void ModeCtlPanel::setChecked(quint16 axis,bool checked)
{
  m_uiCheckComboList.at(axis)->m_checkBox->setChecked(checked);
}

void ModeCtlPanel::setMode(quint16 axis, int mode)
{
  m_uiCheckComboList.at(axis)->m_comboBox->setCurrentIndex(mode);
}

void ModeCtlPanel::keyPressEvent(QKeyEvent *event)
{
  Q_UNUSED(event);
  if(event->key()==Qt::Key_Control)
    m_keyCtlIsPressed=true;
}

void ModeCtlPanel::keyReleaseEvent(QKeyEvent *event)
{
  Q_UNUSED(event);
  if(event->key()==Qt::Key_Control)
    m_keyCtlIsPressed=false;
}

void ModeCtlPanel::onCheckChanged(bool checked)
{
  UiCheckCombo *uibox=qobject_cast<UiCheckCombo *>(sender());
  if(checked)
  {
    qDebug()<<"axis"<<uibox->m_axisNum<<"checked"<<checked;
    if(!m_keyCtlIsPressed)
    {
      for(int i=0;i<m_uiCheckComboList.size();i++)
      {
        if(uibox->m_axisNum==i)
          continue;
        m_uiCheckComboList.at(i)->m_checkBox->setChecked(false);
      }
    }
    emit checkChanged(uibox->m_axisNum,uibox->m_comboBox->currentIndex());
  }
  else
  {
    bool hasChecked=false;
    for(int i=0;i<m_uiCheckComboList.size();i++)
    {
      if(m_uiCheckComboList.at(i)->m_checkBox->isChecked())
        hasChecked=true;
    }
    if(hasChecked==false)
      uibox->m_checkBox->setChecked(true);
  }
}

void ModeCtlPanel::onModeChanged(int mode)
{
  UiCheckCombo *uibox=qobject_cast<UiCheckCombo *>(sender());
  qDebug()<<"axis"<<uibox->m_axisNum<<"mode"<<mode;
  emit modeChanged(uibox->m_axisNum,uibox->m_comboBox->currentIndex());

  for(int i=0;i<m_uiCheckComboList.size();i++)
  {
    m_uiCheckComboList.at(i)->m_checkBox->setChecked(false);
  }
  uibox->m_checkBox->setChecked(true);
}

void ModeCtlPanel::clearUiCheckComboList()
{
  for(int i=0;i<m_uiCheckComboList.size();i++)
  {
    UiCheckCombo *uiBox=m_uiCheckComboList.at(i);
    disconnect(uiBox,SIGNAL(checkChanged(bool)),this,SLOT(onCheckChanged(bool)));
    disconnect(uiBox,SIGNAL(modeChanged(int)),this,SLOT(onModeChanged(int)));
    delete uiBox;
  }
  m_uiCheckComboList.clear();
}



