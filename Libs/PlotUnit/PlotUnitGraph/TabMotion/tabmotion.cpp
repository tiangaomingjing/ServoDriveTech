#include "tabmotion.h"
#include "ui_tabmotion.h"
#include "Option"
#include "sevdevice.h"
#include "gtutils.h"
#include "imotion.h"
#include "motionvelocity.h"

#include <QMessageBox>
#include <QDebug>
#include <QProgressBar>

#define ICON_NAME_SERVO_ON      "plot_son.png"
#define ICON_NAME_SERVO_OFF     "plot_soff.png"

#define TEST_DEBUG 1

MotionProgressBar::MotionProgressBar(int axisCount, QWidget *parent):QWidget(parent),
  m_axisCount(axisCount)
{
  QHBoxLayout *hlayout = new QHBoxLayout(this);
  for(int i = 0;i<axisCount;i++)
  {
    QProgressBar *bar = new QProgressBar(this);
    bar->setTextVisible(false);
    bar->setOrientation(Qt::Vertical);
    QLabel *label = new QLabel(tr("%1").arg(i+1),this);
    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(bar);
    vlayout->addWidget(label);
    hlayout->addLayout(vlayout);
    m_barList.append(bar);
    bar->setMaximumWidth(10);
    bar->setValue(0);
    bar->setVisible(false);
  }
  hlayout->setSpacing(2);
  hlayout->setContentsMargins(0,0,0,0);
}

MotionProgressBar::~MotionProgressBar()
{

}

void MotionProgressBar::hideAllBar()
{
  for(int i = 0;i<m_barList.size();i++)
    m_barList.at(i)->setVisible(false);
}

void MotionProgressBar::resetAllBarValue()
{
  for(int i = 0;i<m_barList.size();i++)
    m_barList.at(i)->setValue(0);
}

void MotionProgressBar::setBarValue(int axisInx, int value)
{
  m_barList.at(axisInx)->setVisible(true);
  m_barList.at(axisInx)->setValue(value);
}


TabMotion::TabMotion(const QString &name, SevDevice *sev, QWidget *parent) :
  ITabWidget(name,sev,parent),
  ui(new Ui::TabMotion)
{
  ui->setupUi(this);

  ui->tbtn_plot_ctlsrc_glink2->setCheckable(true);
  ui->tbtn_plot_ctlsrc_pc->setCheckable(true);
  ui->tbtn_plot_servoGoMotion->setCheckable(true);
  QStringList axisList;
  for(int i = 0;i<sev->axisNum();i++)
  {
    axisList<<tr("Axis_%1").arg(i+1);
    TabMotionData *data = new TabMotionData;
    m_axisMotionDataList.append(data);
  }
  ui->listWidget_plot_tab2_axis->addItems(axisList);
  ui->listWidget_plot_tab2_axis->setCurrentRow(0);
  ui->listWidget_plot_tab2_axis->setResizeMode(QListView::Adjust);
  ui->listWidget_plot_tab2_axis->setSelectionMode(QAbstractItemView::ExtendedSelection);

  //初始化运动界面
  IMotion *motion = new MotionNone(ui->listWidget_plot_tab2_axis,m_sev,tr("None"));
  for(int i = 0;i<m_axisMotionDataList.size();i++)
  {
    m_axisMotionDataList.at(i)->m_curMotion = motion;
  }
  m_motionList.append(motion);
  MotionVelocity *vMotion  = new MotionVelocity(ui->listWidget_plot_tab2_axis,m_sev,tr("Velocity"));
  connect(vMotion,SIGNAL(progressValueChanged(quint16,int)),this,SLOT(onProgressValueChanged(quint16,int)));
  connect(vMotion,SIGNAL(motionAllDone()),this,SLOT(onMotionAllDone()));
  m_motionList.append(vMotion);

  for(int i=0;i<m_motionList.size();i++)
  {
    ui->listWidget_plot_motion_type_inx->addItem(QString("%1 %2").arg(i).arg(m_motionList.at(i)->name()));
    ui->stackedWidget_motion_container->addWidget(m_motionList.at(i)->ui());
  }
  ui->listWidget_plot_motion_type_inx->setCurrentRow(0);
  ui->stackedWidget_motion_container->setCurrentIndex(0);

  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onCssChanged(QString)));
  setupIcons(face->css());

  m_barWidget = new MotionProgressBar(sev->axisNum(),this);
  ui->verticalLayout_go->insertWidget(0,m_barWidget);
  m_barWidget->setVisible(false);

  connect(ui->listWidget_plot_tab2_axis,SIGNAL(currentRowChanged(int)),this,SLOT(onMotionAxisRowChanged(int)));
  connect(ui->tbtn_plot_ctlsrc_pc,SIGNAL(clicked(bool)),this,SLOT(onBtnCtlSrcPcClicked()));
  connect(ui->tbtn_plot_ctlsrc_glink2,SIGNAL(clicked(bool)),this,SLOT(onBtnCtlSrcGLink2Clicked()));
  connect(ui->listWidget_plot_motion_type_inx,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onListWidgetMotionTypeInxClicked(QListWidgetItem*)));
  connect(ui->tbtn_plot_servoGoMotion,SIGNAL(clicked(bool)),this,SLOT(onBtnMotionGoClicked(bool)));
}

TabMotion::~TabMotion()
{
  qDebug()<<"TabMotion TabMotion TabMotion TabMotion destruct ------->";
//  GT::deepClearList(m_motionList);
//  GT::deepClearList(m_axisMotionDataList);
  delete ui;
}

void TabMotion::uiUpdate()
{
  GT::SevControlSrc src = m_sev->controlSrc(m_currentAxis);
//  qDebug()<<"motion axis = "<<m_currentAxis<<"control src "<<(int)src;
  setUiCurrentCtlSrc(src);
  ui->tbtn_plot_servoGoMotion->setChecked(m_sev->axisServoIsOn(m_currentAxis));
}

void TabMotion::resetUi()
{
  ui->listWidget_plot_tab2_axis->setCurrentRow(0);
  m_currentAxis = 0;
  for(int i = 0;i<m_axisMotionDataList.size();i++)
  {
    m_axisMotionDataList.at(i)->m_curMotion = m_motionList.at(0);
  }
  ui->listWidget_plot_motion_type_inx->setCurrentRow(0);
  ui->stackedWidget_motion_container->setCurrentIndex(0);
  ui->tbtn_plot_servoGoMotion->setEnabled(false);
}

void TabMotion::setupIcons(const QString &css)
{
  QSize iconSize(100,100);
  QString iconPath=GTUtils::customPath()+"option/style/"+css+"/icon/";
  QIcon servoOnIcon;
  servoOnIcon.addPixmap(QPixmap(iconPath+ICON_NAME_SERVO_OFF),QIcon::Selected,QIcon::Off);
  servoOnIcon.addPixmap(QPixmap(iconPath+ICON_NAME_SERVO_ON),QIcon::Selected,QIcon::On);
  ui->tbtn_plot_servoGoMotion->setIcon(servoOnIcon);
  ui->tbtn_plot_servoGoMotion->setIconSize(iconSize);

//  ui->label_vplan_seq->setScaledContents(true);
//  ui->label_vplan_step->setScaledContents(true);
//  ui->label_vplan_seq->setPixmap(QPixmap(iconPath+PIC_NAME_VSEQ));
//  ui->label_vplan_step->setPixmap(QPixmap(iconPath+PIC_NAME_VSTEP));

}
void TabMotion::setUiCurrentCtlSrc(int src)
{
  GT::SevControlSrc sevsrc = (GT::SevControlSrc)src;
  switch (sevsrc) {
  case GT::SEV_CTL_SRC_PC:
    ui->tbtn_plot_ctlsrc_pc->setChecked(true);
    ui->tbtn_plot_ctlsrc_glink2->setChecked(false);
    break;
  case GT::SEV_CTL_SRC_GLINK2:
    ui->tbtn_plot_ctlsrc_pc->setChecked(false);
    ui->tbtn_plot_ctlsrc_glink2->setChecked(true);
    break;
  default:
    break;
  }
  ui->stackedWidget_pc_glink2->setCurrentIndex(src);
}
void TabMotion::onCssChanged(const QString &css)
{
  setupIcons(css);
}

void TabMotion::onMotionAxisRowChanged(int row)
{
  if(row <0)
    return;
  m_currentAxis = row;
  //还原这个轴下已经设置的运动模式
  IMotion::MotionType type = m_axisMotionDataList.at(row)->m_curMotion->motionType();
  qDebug()<<"Motion type "<<type<<"row "<<row;
  ui->listWidget_plot_motion_type_inx->setCurrentRow(type);
  m_motionList.at(type)->updateAxisUi(row);
  if(type == IMotion::MOTION_TYPE_NONE)
    ui->tbtn_plot_servoGoMotion->setEnabled(false);
  else
    ui->tbtn_plot_servoGoMotion->setEnabled(true);
  ui->stackedWidget_motion_container->setCurrentIndex(type);
}
void TabMotion::onBtnCtlSrcPcClicked()
{
  for(int i = 0;i<ui->listWidget_plot_tab2_axis->count();i++)
  {
    if(ui->listWidget_plot_tab2_axis->item(i)->isSelected())
    {
      m_sev->setControlSrc(i,GT::SEV_CTL_SRC_PC);
    }
  }
  setUiCurrentCtlSrc(GT::SEV_CTL_SRC_GLINK2);
}

void TabMotion::onBtnCtlSrcGLink2Clicked()
{
  for(int i = 0;i<ui->listWidget_plot_tab2_axis->count();i++)
  {
    if(ui->listWidget_plot_tab2_axis->item(i)->isSelected())
    {
      m_sev->setControlSrc(i,GT::SEV_CTL_SRC_GLINK2);
    }
  }
  setUiCurrentCtlSrc(GT::SEV_CTL_SRC_GLINK2);
}

void TabMotion::onListWidgetMotionTypeInxClicked(QListWidgetItem *item)
{
  qDebug()<<"motion type index = "<<ui->listWidget_plot_motion_type_inx->currentRow();
  int index=ui->listWidget_plot_motion_type_inx->row(item);//点击了哪一个运动源
  IMotion::MotionType type = (IMotion::MotionType)index;
  switch (type)
  {
  case IMotion::MOTION_TYPE_NONE:
    ui->tbtn_plot_servoGoMotion->setEnabled(false);
    break;
  case IMotion::MOTION_TYPE_VEL:
    ui->tbtn_plot_servoGoMotion->setEnabled(true);
    break;
  default:
    break;
  }
  quint16 curAxis = ui->listWidget_plot_tab2_axis->currentRow();
  m_motionList.at(type)->updateAxisUi(curAxis);

  for(int row = 0;row<ui->listWidget_plot_tab2_axis->count();row++)
  {
    if(ui->listWidget_plot_tab2_axis->item(row)->isSelected())
    {
      m_axisMotionDataList.at(row)->m_curMotion = m_motionList.at(index);
    }
  }
  ui->stackedWidget_motion_container->setCurrentIndex(type);
}

void TabMotion::onBtnMotionGoClicked(bool checked)
{
  if(!m_sev->isConnecting())
  {
    ui->tbtn_plot_servoGoMotion->setChecked(false);
    return ;
  }

  if(checked)
  {
    quint16 axis =0;
    emit motionStart();
    for(int row = 0;row<ui->listWidget_plot_tab2_axis->count();row++)
    {
      axis = row;
      if(ui->listWidget_plot_tab2_axis->item(row)->isSelected())
      {
        m_axisMotionDataList.at(axis)->m_curMotion->movePrepare(axis);
      }
    }
    qDebug()<<"movePrepare delay";
    OptPlot *plot = dynamic_cast<OptPlot *>(OptContainer::instance()->optItem("optplot"));
    GTUtils::delayms(plot->delayTime());
    qDebug()<<"begin to move";

    for(int row = 0;row<ui->listWidget_plot_tab2_axis->count();row++)
    {
      axis = row;
      if(ui->listWidget_plot_tab2_axis->item(row)->isSelected())
      {
        m_axisMotionDataList.at(axis)->m_curMotion->move(axis);
      }
    }
    m_barWidget->setVisible(true);

    m_barWidget->resetAllBarValue();
  }
  else
  {
    for(int row = 0;row<ui->listWidget_plot_tab2_axis->count();row++)
    {
      if(ui->listWidget_plot_tab2_axis->item(row)->isSelected())
      {
        m_axisMotionDataList.at(row)->m_curMotion->stop(row);
      }
    }
    m_barWidget->setVisible(false);
    m_barWidget->hideAllBar();
  }
}

void TabMotion::onProgressValueChanged(quint16 axisInx, int value)
{
  m_barWidget->setBarValue(axisInx,value);
}

void TabMotion::onMotionAllDone()
{
  GTUtils::delayms(10);
  emit motionStop();
}

