#include "velpid133.h"
#include "ui_velpid133.h"
#include "Option"
#include "gtutils.h"

#include <QStyledItemDelegate>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>
#include <QDoubleSpinBox>

#define PIC_VEL_PID_HELP_NAME "vel_pid_segment_help.png"

VelPid133::VelPid133(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::VelPid133)
{
  ui->setupUi(this);

  QStringList list;
  list<<tr("1")<<tr("2")<<tr("3");
  ui->comboBox->addItems(list);
  QStyledItemDelegate* itemDelegate = new QStyledItemDelegate(ui->comboBox);
  ui->comboBox->setItemDelegate(itemDelegate);


  ui->label_title->setObjectName("label_velPidTitle");
  ui->label_title->setAlignment(Qt::AlignCenter);

  m_helpPic = new QLabel;
  m_helpPic->setWindowTitle(tr("Velocity PID Config Help"));

  connect(ui->btn_configHelp,SIGNAL(clicked(bool)),this,SLOT(onBtnConfigHelpClicked()));
  connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxIndexChanged(int)));
}

VelPid133::~VelPid133()
{
  delete ui;
  delete m_helpPic;
}

QDoubleSpinBox *VelPid133::boxP1()
{
  return ui->doubleSpinBox_p1;
}

QDoubleSpinBox *VelPid133::boxI1()
{
  return ui->doubleSpinBox_i1;
}

QDoubleSpinBox *VelPid133::boxP2()
{
  return ui->doubleSpinBox_p2;
}

QDoubleSpinBox *VelPid133::boxI2()
{
  return ui->doubleSpinBox_i2;
}

QDoubleSpinBox *VelPid133::boxTime()
{
  return ui->doubleSpinBox_ts;
}

QDoubleSpinBox *VelPid133::boxSpdu()
{
  return ui->doubleSpinBox_spdu;
}

QDoubleSpinBox *VelPid133::boxSpdl()
{
  return ui->doubleSpinBox_spdl;
}

void VelPid133::setCurrentPidSegment(int index)
{
  setPidSegmentUi(index);
  ui->comboBox->setCurrentIndex(index);
}

void VelPid133::setPidSegmentUi(int index)
{
  switch(index)
  {
  case 0:
    ui->doubleSpinBox_p2->setVisible(false);
    ui->doubleSpinBox_i2->setVisible(false);
    ui->doubleSpinBox_spdl->setVisible(false);
    ui->doubleSpinBox_spdu->setVisible(false);
    ui->doubleSpinBox_ts->setVisible(false);
    ui->label_p2->setVisible(false);
    ui->label_i2->setVisible(false);
    ui->label_spdl->setVisible(false);
    ui->label_spdu->setVisible(false);
    ui->label_ts->setVisible(false);
    ui->line_2->setVisible(false);
    ui->line_3->setVisible(false);
    ui->btn_configHelp->setVisible(false);
    break;
  case 1:
  case 2:
  case 3:
    ui->doubleSpinBox_p2->setVisible(true);
    ui->doubleSpinBox_i2->setVisible(true);
    ui->doubleSpinBox_spdl->setVisible(true);
    ui->doubleSpinBox_spdu->setVisible(true);
    ui->doubleSpinBox_ts->setVisible(true);
    ui->label_p2->setVisible(true);
    ui->label_i2->setVisible(true);
    ui->label_spdl->setVisible(true);
    ui->label_spdu->setVisible(true);
    ui->label_ts->setVisible(true);
    ui->line_2->setVisible(true);
    ui->line_3->setVisible(true);
    ui->btn_configHelp->setVisible(true);
    break;
  default:
    ui->doubleSpinBox_p2->setVisible(false);
    ui->doubleSpinBox_i2->setVisible(false);
    ui->doubleSpinBox_spdl->setVisible(false);
    ui->doubleSpinBox_spdu->setVisible(false);
    ui->doubleSpinBox_ts->setVisible(false);
    ui->label_p2->setVisible(false);
    ui->label_i2->setVisible(false);
    ui->label_spdl->setVisible(false);
    ui->label_spdu->setVisible(false);
    ui->label_ts->setVisible(false);
    ui->line_2->setVisible(false);
    ui->line_3->setVisible(false);
    ui->btn_configHelp->setVisible(false);
    break;
  }
}

void VelPid133::onComboBoxIndexChanged(int index)
{
  if(index == -1)
    return ;
  setPidSegmentUi(index);
  emit comboBoxIndexChanged(index);
}

void VelPid133::onBtnConfigHelpClicked()
{
  OptFace *face = dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QString css = face->css();
  QString picPath = GTUtils::customPath()+"option/style/"+css+"/icon/"+PIC_VEL_PID_HELP_NAME;
  m_helpPic->setPixmap(QPixmap(picPath));
  m_helpPic->show();
}
