#include "tabctlpanel129.h"
#include "ui_tabctlpanel129.h"
#include "sevdevice.h"
#include "gtutils.h"
#include "Option"

#include <QDebug>
#include <QKeyEvent>

#define ICON_NAME_SERVO_ON      "plot_son.png"
#define ICON_NAME_SERVO_OFF     "plot_soff.png"
#define PIC_NAME_VSTEP          "plot_vstep.png"
#define PIC_NAME_VSEQ           "plot_vseq.png"

typedef enum{
  TAB_MODE,
  TAB_MOTION
}TabInx;

TabCtlPanel129::TabCtlPanel129(SevDevice *sev, QWidget *parent) : QWidget(parent),
  ui(new Ui::TabCtlPanel129),
  m_sev(sev)
{
  ui->setupUi(this);
  m_data=new PlotTabCtlPrms(sev->axisNum());
  ui->modeCtlPanel->setAxisCount(sev->axisNum());
  ui->tabWidget->setTabText(TAB_MODE,tr("ModeCtl"));
  ui->tabWidget->setTabText(TAB_MOTION,tr("Motion"));

  //tab mode
  ui->spinBox_mode_idref->installEventFilter(this);
  ui->spinBox_mode_ipa->installEventFilter(this);
  ui->spinBox_mode_iqref->installEventFilter(this);
  ui->spinBox_mode_uaref->installEventFilter(this);
  ui->spinBox_mode_ubref->installEventFilter(this);
  ui->spinBox_mode_ucref->installEventFilter(this);
  ui->spinBox_mode_udref->installEventFilter(this);
  ui->spinBox_mode_uqref->installEventFilter(this);
  ui->spinBox_mode_vcl->installEventFilter(this);
  ui->spinBox_mode_vpl->installEventFilter(this);
  ui->spinBox_mode_vsl->installEventFilter(this);
  ui->spinBox_mode_pt->installEventFilter(this);

  ui->tbtn_plot_servoOnMode->setCheckable(true);
  ui->tbtn_plot_servoGoMotion->setCheckable(true);
  ui->label_plot_servo_onoff->setText(tr("SEV OFF"));

  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  setupIcons(face->css());

  //tab motion
  ui->stackedWidget_vel_plan->setCurrentIndex(0);
  ui->tbtn_plot_ctlsrc_glink2->setCheckable(true);
  ui->tbtn_plot_ctlsrc_pc->setCheckable(true);
  QStringList axisList;
  for(int i = 0;i<sev->axisNum();i++)
  {
    axisList<<tr("Axis_%1").arg(i+1);
  }
  ui->listWidget_plot_tab2_axis->addItems(axisList);
  ui->listWidget_plot_tab2_axis->setCurrentRow(0);
  ui->listWidget_plot_tab2_axis->setResizeMode(QListView::Adjust);
  ui->listWidget_plot_tab2_axis->setSelectionMode(QAbstractItemView::ExtendedSelection);


  //tab mode
  connect(ui->modeCtlPanel,SIGNAL(checkChanged(quint16,int)),this,SLOT(onModeCtlPanelCheckChanged(quint16,int)));
  connect(ui->modeCtlPanel,SIGNAL(modeChanged(quint16,int)),this,SLOT(onModeCtlPanelModeChanged(quint16,int)));
  connect(ui->spinBox_mode_idref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_ipa,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_iqref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_uaref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_ubref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_ucref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_udref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_uqref,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_vcl,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_vpl,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_vsl,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->spinBox_mode_pt,SIGNAL(valueChanged(int)),this,SLOT(onModeSpinBoxValueChanged(int)));
  connect(ui->tbtn_plot_servoOnMode,SIGNAL(clicked(bool)),this,SLOT(onBtnServoOnClicked(bool)));
  //tab motion
  connect(ui->checkBox_circleSw,SIGNAL(clicked(bool)),this,SLOT(onCheckBoxCircleSWClicked()));
  connect(ui->listWidget_plot_tab2_axis,SIGNAL(currentRowChanged(int)),this,SLOT(onMotionAxisRowChanged(int)));
  connect(ui->tbtn_plot_ctlsrc_pc,SIGNAL(clicked(bool)),this,SLOT(onBtnCtlSrcPcClicked()));
  connect(ui->tbtn_plot_ctlsrc_glink2,SIGNAL(clicked(bool)),this,SLOT(onBtnCtlSrcGLink2Clicked()));
}

TabCtlPanel129::~TabCtlPanel129()
{
  delete m_data;
}

void TabCtlPanel129::setupIcons(const QString &css)
{
  QSize iconSize(100,100);
  QString iconPath=GTUtils::customPath()+"option/style/"+css+"/icon/";
  QIcon servoOnIcon;
  servoOnIcon.addPixmap(QPixmap(iconPath+ICON_NAME_SERVO_OFF),QIcon::Selected,QIcon::Off);
  servoOnIcon.addPixmap(QPixmap(iconPath+ICON_NAME_SERVO_ON),QIcon::Selected,QIcon::On);
  ui->tbtn_plot_servoOnMode->setIcon(servoOnIcon);
  ui->tbtn_plot_servoOnMode->setIconSize(iconSize);
  ui->tbtn_plot_servoGoMotion->setIcon(servoOnIcon);
  ui->tbtn_plot_servoGoMotion->setIconSize(iconSize);

//  ui->tbtn_icon_vplan_seq->setIcon(QPixmap(iconPath+PIC_NAME_VSEQ));
//  ui->tbtn_icon_vplan_step->setIcon(QPixmap(iconPath+PIC_NAME_VSTEP));
//  ui->tbtn_icon_vplan_seq->setIconSize(QSize(520,110));
//  ui->tbtn_icon_vplan_seq->setIconSize(QSize(520,110));
  ui->label_vplan_seq->setScaledContents(true);
  ui->label_vplan_step->setScaledContents(true);
  ui->label_vplan_seq->setPixmap(QPixmap(iconPath+PIC_NAME_VSEQ));
  ui->label_vplan_step->setPixmap(QPixmap(iconPath+PIC_NAME_VSTEP));

}

void TabCtlPanel129::updateServoStatus()
{
  if(!m_sev->isConnecting())
    return ;
  //tab1
  quint16 curModeAxis = m_data->m_curModeAxis;
  quint16 curMotionAxis = m_data->m_curMotionAxis;
  for(int i=0;i<m_sev->axisNum();i++)
  {
    ui->modeCtlPanel->setMode(i,m_sev->currentTaskServoMode(i));
  }

  ui->stackedWidget_plot_mode->setCurrentIndex(ui->modeCtlPanel->mode(curModeAxis));

  ui->tbtn_plot_servoOnMode->setChecked(m_sev->axisServoIsOn(curModeAxis));
  qDebug()<<"update servo status"<<m_sev->aliasName()<<" cur mode axis = "<<curModeAxis<<" servo on = "<<m_sev->axisServoIsOn(curModeAxis);

  //tab2
  GT::SevControlSrc src = m_sev->controlSrc(curMotionAxis);
  qDebug()<<"motion axis = "<<curMotionAxis<<"control src "<<(int)src;
  setUiCurrentCtlSrc(src);
}

bool TabCtlPanel129::eventFilter(QObject *obj, QEvent *event)
{
  if(event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      //tab mode
      PlotTabCtlPrms *prms=m_data;
      ModeCtlPrms* modePrms=prms->m_modeCtlPrmsList.at(prms->m_curModeAxis);
      QSpinBox *box=qobject_cast<QSpinBox *>(obj);
      quint16 axisInx = prms->m_curModeAxis;
      qDebug()<<"spinBox value"<<box->value();
      if(obj==ui->spinBox_mode_ipa)//3 初始化相位
      {
        modePrms->m_ipa=ui->spinBox_mode_ipa->value();

        m_sev->cmdSetPosAdjRef(axisInx,modePrms->m_ipa);
        ui->spinBox_mode_ipa->setStyleSheet("color:black");
      }
      else if(obj==ui->spinBox_mode_uaref||obj==ui->spinBox_mode_ubref\
              ||obj==ui->spinBox_mode_ucref||obj==ui->spinBox_mode_udref\
              ||obj==ui->spinBox_mode_udref||obj==ui->spinBox_mode_uqref) //4 电压开环调试
      {
        modePrms->m_uaref=ui->spinBox_mode_uaref->value();
        modePrms->m_ubref=ui->spinBox_mode_ubref->value();
        modePrms->m_ucref=ui->spinBox_mode_ucref->value();
        modePrms->m_udref=ui->spinBox_mode_udref->value();
        modePrms->m_uqref=ui->spinBox_mode_uqref->value();

        m_sev->cmdSetUaRef(axisInx,modePrms->m_uaref);
        m_sev->cmdSetUbRef(axisInx,modePrms->m_ubref);
        m_sev->cmdSetUcRef(axisInx,modePrms->m_ucref);
        m_sev->cmdSetUdRef(axisInx,modePrms->m_udref);
        m_sev->cmdSetUqRef(axisInx,modePrms->m_uqref);

        ui->spinBox_mode_uaref->setStyleSheet("color:black");
        ui->spinBox_mode_ubref->setStyleSheet("color:black");
        ui->spinBox_mode_ucref->setStyleSheet("color:black");
        ui->spinBox_mode_udref->setStyleSheet("color:black");
        ui->spinBox_mode_uqref->setStyleSheet("color:black");
      }
      else if(obj==ui->spinBox_mode_idref||obj==ui->spinBox_mode_iqref)   //5 电流闭环调试
      {
        modePrms->m_idref=ui->spinBox_mode_idref->value();
        modePrms->m_iqref=ui->spinBox_mode_iqref->value();

        m_sev->cmdSetIdRef(axisInx,modePrms->m_idref);
        m_sev->cmdSetIqRef(axisInx,modePrms->m_idref);
        ui->spinBox_mode_idref->setStyleSheet("color:black");
        ui->spinBox_mode_iqref->setStyleSheet("color:black");
      }
      else if(obj==ui->spinBox_mode_vcl)                                  //6 速度闭环调试
      {
        modePrms->m_vcl=ui->spinBox_mode_vcl->value();

        m_sev->cmdSetSpdRef(axisInx,modePrms->m_vcl);
        ui->spinBox_mode_vcl->setStyleSheet("color:black");
      }
      else if(obj==ui->spinBox_mode_vpl)                                  //7 轮廓速度跟踪
      {
        modePrms->m_vpl=ui->spinBox_mode_vpl->value();

        m_sev->cmdSetSpdRef(axisInx,modePrms->m_vpl);
        ui->spinBox_mode_vpl->setStyleSheet("color:black");
      }
      else if(obj==ui->spinBox_mode_vsl)                                  //8 周期同步速度跟踪
      {
        modePrms->m_vsl=ui->spinBox_mode_vsl->value();

        m_sev->cmdSetSpdRef(axisInx,modePrms->m_vsl);
        ui->spinBox_mode_vsl->setStyleSheet("color:black");
      }
      else if(obj==ui->spinBox_mode_pt)                                  //8 周期同步位置跟踪
      {
        modePrms->m_pt=ui->spinBox_mode_pt->value();

        m_sev->cmdSetPosRef(axisInx,modePrms->m_pt);
        ui->spinBox_mode_pt->setStyleSheet("color:black");
      }
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}

void TabCtlPanel129::onModeCtlPanelCheckChanged(quint16 axis, int mode)
{
  qDebug()<<axis<<mode;
  //还原对应轴的参数设置
  if(mode<ui->stackedWidget_plot_mode->count())
  {
    PlotTabCtlPrms *prms=m_data;
    prms->m_curModeAxis=axis;
    ModeCtlPrms* modePrms=prms->m_modeCtlPrmsList.at(axis);
    modePrms->m_curMode=(ModeCtlPrms::ModeCtlType)mode;
    ui->stackedWidget_plot_mode->setCurrentIndex(mode);
    switch(mode)
    {
    case ModeCtlPrms::MODE_IDLE:break;
    case ModeCtlPrms::MODE_ADC:break;
    case ModeCtlPrms::MODE_IPA:
    {
      ui->spinBox_mode_ipa->setValue(modePrms->m_ipa);
    }
    break;
    case ModeCtlPrms::MODE_MPI:break;
    case ModeCtlPrms::MODE_COL:
    {
      ui->spinBox_mode_uaref->setValue(modePrms->m_uaref);
      ui->spinBox_mode_ubref->setValue(modePrms->m_ubref);
      ui->spinBox_mode_ucref->setValue(modePrms->m_ucref);
      ui->spinBox_mode_udref->setValue(modePrms->m_udref);
      ui->spinBox_mode_uqref->setValue(modePrms->m_uqref);
    }
    break;
    case ModeCtlPrms::MODE_CCL:
    {
      ui->spinBox_mode_idref->setValue(modePrms->m_idref);
      ui->spinBox_mode_iqref->setValue(modePrms->m_iqref);
    }
    break;
    case ModeCtlPrms::MODE_VCL:
    {
      ui->spinBox_mode_vcl->setValue(modePrms->m_vcl);
    }
    break;
    case ModeCtlPrms::MODE_VPL:
    {
      ui->spinBox_mode_vpl->setValue(modePrms->m_vpl);
    }
    break;
    case ModeCtlPrms::MODE_VSL:
    {
      ui->spinBox_mode_vsl->setValue(modePrms->m_vsl);
    }
    break;
    case ModeCtlPrms::MODE_FIX:break;
    case ModeCtlPrms::MODE_PT:
    {
      ui->spinBox_mode_pt->setValue(modePrms->m_pt);
    }
    break;
    case ModeCtlPrms::MODE_DB:break;
    case ModeCtlPrms::MODE_CSC:break;
    }
  }
}

void TabCtlPanel129::onModeCtlPanelModeChanged(quint16 axis, int mode)
{
  qDebug()<<axis<<mode;
  if(mode<ui->stackedWidget_plot_mode->count())
  {
    PlotTabCtlPrms *prms=m_data;
    prms->m_curModeAxis=axis;
    ModeCtlPrms* modePrms=prms->m_modeCtlPrmsList.at(axis);
    modePrms->m_curMode=(ModeCtlPrms::ModeCtlType)mode;
    ui->stackedWidget_plot_mode->setCurrentIndex(mode);
    m_sev->setCurrentTaskServoMode(axis,mode);//下发实际指令
    switch(mode)
    {
    case ModeCtlPrms::MODE_IDLE:break;
    case ModeCtlPrms::MODE_ADC:break;
    case ModeCtlPrms::MODE_IPA:
    {
      ui->spinBox_mode_ipa->setValue(modePrms->m_ipa);
    }
    break;
    case ModeCtlPrms::MODE_MPI:break;
    case ModeCtlPrms::MODE_COL:
    {
      ui->spinBox_mode_uaref->setValue(modePrms->m_uaref);
      ui->spinBox_mode_ubref->setValue(modePrms->m_ubref);
      ui->spinBox_mode_ucref->setValue(modePrms->m_ucref);
      ui->spinBox_mode_udref->setValue(modePrms->m_udref);
      ui->spinBox_mode_uqref->setValue(modePrms->m_uqref);
    }
    break;
    case ModeCtlPrms::MODE_CCL:
    {
      ui->spinBox_mode_idref->setValue(modePrms->m_idref);
      ui->spinBox_mode_iqref->setValue(modePrms->m_iqref);
    }
    break;
    case ModeCtlPrms::MODE_VCL:
    {
      ui->spinBox_mode_vcl->setValue(modePrms->m_vcl);
    }
    break;
    case ModeCtlPrms::MODE_VPL:
    {
      ui->spinBox_mode_vpl->setValue(modePrms->m_vpl);
    }
    break;
    case ModeCtlPrms::MODE_VSL:
    {
      ui->spinBox_mode_vsl->setValue(modePrms->m_vsl);
    }
    break;
    case ModeCtlPrms::MODE_FIX:break;
    case ModeCtlPrms::MODE_PT:
    {
      ui->spinBox_mode_pt->setValue(modePrms->m_pt);
    }
    break;
    case ModeCtlPrms::MODE_DB:break;
    case ModeCtlPrms::MODE_CSC:break;
    }
  }
}

void TabCtlPanel129::onModeSpinBoxValueChanged(int value)
{
  Q_UNUSED(value);
  QSpinBox *box = qobject_cast<QSpinBox *>(sender());
  box->setStyleSheet("color:red");
}

void TabCtlPanel129::onBtnServoOnClicked(bool checked)
{
  if(!m_sev->isConnecting())
  {
    ui->tbtn_plot_servoOnMode->setChecked(false);
    return ;
  }
  for(int i = 0;i<ui->modeCtlPanel->axisCount();i++)
  {
    if(ui->modeCtlPanel->isChecked(i))
    {
      m_sev->setAxisServoOn(i,checked);
      qDebug()<<"setServoOn "<<i<<checked;
      qDebug()<<"----------sev axis is on"<<m_sev->axisServoIsOn(i)<<"-----------";
    }
  }
}

void TabCtlPanel129::onCheckBoxCircleSWClicked()
{
  if(ui->checkBox_circleSw->isChecked())
    ui->stackedWidget_vel_plan->setCurrentIndex(1);
  else
    ui->stackedWidget_vel_plan->setCurrentIndex(0);
}

void TabCtlPanel129::onMotionAxisRowChanged(int row)
{
  m_data->m_curMotionAxis = row;
}

void TabCtlPanel129::onBtnCtlSrcPcClicked()
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

void TabCtlPanel129::onBtnCtlSrcGLink2Clicked()
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

void TabCtlPanel129::setUiCurrentCtlSrc(int src)
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

