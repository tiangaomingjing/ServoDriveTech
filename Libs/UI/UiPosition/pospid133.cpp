#include "pospid133.h"
#include "ui_pospid133.h"
#include "Option"
#include "gtutils.h"

#include <QStyledItemDelegate>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>

#define PIC_POS_PID_HELP_NAME "pos_pid_segment_help.png"

PosPID133::PosPID133(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PosPID133)
{
  ui->setupUi(this);

  QStringList list;
  list<<tr("1")<<tr("2")<<tr("3");
  ui->comboBox_kpsw->addItems(list);
  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(ui->comboBox_kpsw);
  ui->comboBox_kpsw->setItemDelegate(itemDelegate);
  connect(ui->comboBox_kpsw,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxIndexChanged(int)));

  ui->label_title->setObjectName("label_posPidTitle");
  ui->label_title->setAlignment(Qt::AlignCenter);
  m_btnHelp = new QPushButton(this);
  connect(m_btnHelp,SIGNAL(clicked(bool)),this,SLOT(onBtnConfigHelpClicked()));
  m_btnHelp->setText(tr("config help"));
  ui->gridLayout->addWidget(m_btnHelp,9,0,1,2);
  m_helpPic = new QLabel;
  m_helpPic->setWindowTitle(tr("Position PID Config Help"));

}

PosPID133::~PosPID133()
{
  delete ui;
  delete m_helpPic;
}

QDoubleSpinBox *PosPID133::boxFirstFn()
{
  return ui->doubleSpinBox_P1;
}

QDoubleSpinBox *PosPID133::boxSecondFn()
{
  return ui->doubleSpinBox_P2;
}

QDoubleSpinBox *PosPID133::boxTransTime()
{
  return ui->doubleSpinBox_ts;
}

QDoubleSpinBox *PosPID133::boxSpdUp()
{
  return ui->doubleSpinBox_spdup;
}

QDoubleSpinBox *PosPID133::boxSpdLow()
{
  return ui->doubleSpinBox_spdlow;
}

int PosPID133::currentPidSegmentIndex()
{
  return ui->comboBox_kpsw->currentIndex();
}

void PosPID133::setCurrentPidSegment(int index)
{
  ui->comboBox_kpsw->setCurrentIndex(index);
  onComboBoxIndexChanged(index);
}


void PosPID133::onComboBoxIndexChanged(int index)
{
  if(index == -1)
    return ;
  switch(index)
  {
  case 0:
    ui->doubleSpinBox_P2->setVisible(false);
    ui->doubleSpinBox_spdlow->setVisible(false);
    ui->doubleSpinBox_spdup->setVisible(false);
    ui->doubleSpinBox_ts->setVisible(false);
    ui->label_kp2->setVisible(false);
    ui->label_spdl->setVisible(false);
    ui->label_spdu->setVisible(false);
    ui->label_ts->setVisible(false);
    ui->line_2->setVisible(false);
    m_btnHelp->setVisible(false);
    break;
  case 1:
  case 2:
  case 3:
    ui->doubleSpinBox_P2->setVisible(true);
    ui->doubleSpinBox_spdlow->setVisible(true);
    ui->doubleSpinBox_spdup->setVisible(true);
    ui->doubleSpinBox_ts->setVisible(true);
    ui->label_kp2->setVisible(true);
    ui->label_spdl->setVisible(true);
    ui->label_spdu->setVisible(true);
    ui->label_ts->setVisible(true);
    ui->line_2->setVisible(true);
    m_btnHelp->setVisible(true);
    break;
  default:
    ui->doubleSpinBox_P2->setVisible(false);
    ui->doubleSpinBox_spdlow->setVisible(false);
    ui->doubleSpinBox_spdup->setVisible(false);
    ui->doubleSpinBox_ts->setVisible(false);
    ui->label_kp2->setVisible(false);
    ui->label_spdl->setVisible(false);
    ui->label_spdu->setVisible(false);
    ui->label_ts->setVisible(false);
    ui->line_2->setVisible(false);
    m_btnHelp->setVisible(false);
    break;
  }

  emit comboBoxIndexChanged(index);
}

void PosPID133::onBtnConfigHelpClicked()
{
  OptFace *face = dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QString css = face->css();
  QString picPath = GTUtils::customPath()+"option/style/"+css+"/icon/"+PIC_POS_PID_HELP_NAME;
  m_helpPic->setPixmap(QPixmap(picPath));
  m_helpPic->show();
}
