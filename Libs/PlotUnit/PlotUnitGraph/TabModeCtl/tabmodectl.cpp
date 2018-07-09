#include "tabmodectl.h"
#include "ui_tabmodectl.h"
#include "sevdevice.h"
#include "Option"
#include "gtutils.h"
#include "sdtglobaldef.h"

#include <QDebug>
#include <QKeyEvent>
#include <QStyledItemDelegate>


#define ICON_NAME_SERVO_ON      "plot_son.png"
#define ICON_NAME_SERVO_OFF     "plot_soff.png"

#define GEN_CMD_ACC "gSevDrv.sev_obj.pos.mkr.prm.accrate"
#define GEN_CMD_DEC "gSevDrv.sev_obj.pos.mkr.prm.decrate"
#define GEN_CMD_MOVEMODE "gSevDrv.sev_obj.pos.seq.prm.move_mode"
#define GEN_CMD_MAXVEL "gSevDrv.sev_obj.pos.mkr.prm.maxspd"

class ModeCtlPrms
{
public:
  ModeCtlPrms():m_isChecked(false),
    m_curMode(GT::MODE_IDLE),m_ipa(0),m_uaref(0),m_ubref(0),m_ucref(0),m_udref(0),
    m_uqref(0),m_idref(0),m_iqref(0),m_vcl(0),m_vpl(0),m_vsl(0),m_pt(0),m_autAcc(0),
    m_autDec(0),m_autfgd(0),m_autfgi(0),m_autfgn(0),m_autfgp(0),m_autPulse(0),m_autVel(0)
  {

  }

  bool m_isChecked;
  GT::ModeCtlType m_curMode;
  //mode ipa
  qreal m_ipa;
  //mode col
  qreal m_uaref;
  qreal m_ubref;
  qreal m_ucref;
  qreal m_udref;
  qreal m_uqref;
  //mode ccl
  qreal m_idref;
  qreal m_iqref;
  //mode vcl
  qreal m_vcl;
  //mode vpl
  qreal m_vpl;
  //mode vsl
  qreal m_vsl;
  //mode pt
  qreal m_pt;

  //mode aut
  qreal m_autDec;
  qreal m_autAcc;
  qreal m_autVel;
  qreal m_autPulse;

  qreal m_autfgd;
  qreal m_autfgp;
  qreal m_autfgi;
  qreal m_autfgn;
};


TabModeCtl::TabModeCtl(const QString &name, SevDevice *sev, QWidget *parent) :
  ITabWidget(name,sev,parent),
  ui(new Ui::TabModeCtl),
  m_currenAxis(0)
{
  ui->setupUi(this);

  ui->modeCtlPanel->setAxisCount(sev->axisNum());
  for(int i=0;i<sev->axisNum();i++)
  {
    ModeCtlPrms *mode=new ModeCtlPrms;
    m_dataList.append(mode);
  }

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

  ui->doubleSpinBox_mode_autAcc->installEventFilter(this);
  ui->doubleSpinBox_mode_autDec->installEventFilter(this);
  ui->doubleSpinBox_mode_autMaxVel->installEventFilter(this);
  ui->doubleSpinBox_mode_aut_pulse->installEventFilter(this);

  ui->tbtn_plot_servoOnMode->setCheckable(true);
  ui->label_plot_servo_onoff->setText(tr("SEV OFF"));

  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onCssChanged(QString)));
  setupIcons(face->css());

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
  connect(ui->doubleSpinBox_mode_aut_pulse, SIGNAL(valueChanged(double)), this, SLOT(onModeDoubleSpinBoxValueChanged(double)));
  connect(ui->doubleSpinBox_mode_autAcc, SIGNAL(valueChanged(double)), this, SLOT(onModeDoubleSpinBoxValueChanged(double)));
  connect(ui->doubleSpinBox_mode_autDec, SIGNAL(valueChanged(double)), this, SLOT(onModeDoubleSpinBoxValueChanged(double)));
  connect(ui->doubleSpinBox_mode_autMaxVel, SIGNAL(valueChanged(double)), this, SLOT(onModeDoubleSpinBoxValueChanged(double)));
  connect(ui->tbtn_plot_servoOnMode,SIGNAL(clicked(bool)),this,SLOT(onBtnServoOnClicked(bool)));
}

TabModeCtl::~TabModeCtl()
{
  qDebug()<<"TabModeCtl TabModeCtl TabModeCtl destruct ----->";
  GT::deepClearList(m_dataList);
  delete ui;

}

void TabModeCtl::uiUpdate()
{
  quint16 curModeAxis = m_currenAxis;
  for(int i=0;i<m_sev->axisNum();i++)
  {
    ui->modeCtlPanel->setMode(i,m_sev->currentTaskServoMode(i));
  }

  ui->stackedWidget_plot_mode->setCurrentIndex(ui->modeCtlPanel->mode(curModeAxis));

  ui->tbtn_plot_servoOnMode->setChecked(m_sev->axisServoIsOn(curModeAxis));
  if(ui->tbtn_plot_servoOnMode->isChecked())
    ui->label_plot_servo_onoff->setText(tr("SEV ON"));
  else
    ui->label_plot_servo_onoff->setText(tr("SEV OFF"));
  //qDebug()<<"update servo status"<<m_sev->aliasName()<<" cur mode axis = "<<curModeAxis<<" servo on = "<<m_sev->axisServoIsOn(curModeAxis);

}

void TabModeCtl::resetUi()
{

}

void TabModeCtl::setupIcons(const QString &css)
{
  QSize iconSize(100,100);
  QString iconPath=GTUtils::customPath()+"option/style/"+css+"/icon/";
  QIcon servoOnIcon;
  servoOnIcon.addPixmap(QPixmap(iconPath+ICON_NAME_SERVO_OFF),QIcon::Selected,QIcon::Off);
  servoOnIcon.addPixmap(QPixmap(iconPath+ICON_NAME_SERVO_ON),QIcon::Selected,QIcon::On);
  ui->tbtn_plot_servoOnMode->setIcon(servoOnIcon);
  ui->tbtn_plot_servoOnMode->setIconSize(iconSize);
}

bool TabModeCtl::eventFilter(QObject *obj, QEvent *event)
{
  if(event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      //tab mode
      ModeCtlPrms* modePrms=m_dataList.at(m_currenAxis);

      //QSpinBox *box=qobject_cast<QSpinBox *>(obj);
      quint16 axisInx = m_currenAxis;
      //qDebug()<<"spinBox value"<<box->value();
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
        m_sev->cmdSetIqRef(axisInx,modePrms->m_iqref);

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
      else if (ui->stackedWidget_plot_mode->currentIndex() == 13) {
          bool ok;
          quint64 nos = m_sev->genCmdReadNos(axisInx, ok);
          double scale = nos / (pow(2, 24));
          modePrms->m_autAcc = ui->doubleSpinBox_mode_autAcc->value();
          modePrms->m_autDec = ui->doubleSpinBox_mode_autDec->value();
          modePrms->m_autVel = ui->doubleSpinBox_mode_autMaxVel->value() / scale;
          modePrms->m_autPulse = ui->doubleSpinBox_mode_aut_pulse->value() * 65536;
          m_sev->genCmdWritePlanSpdAcc(axisInx, modePrms->m_autAcc);
          m_sev->genCmdWritePlanSpdDec(axisInx, modePrms->m_autDec);
          m_sev->genCmdWritePlanSpdMax(axisInx, modePrms->m_autVel);
          m_sev->cmdSetPosRef(axisInx, modePrms->m_autPulse);

          modePrms->m_autfgd = m_sev->genCmdReadAutoTurnningFgd(axisInx, ok);
          ui->label_mode_aut_fgd->setText(QString::number(modePrms->m_autfgd));
          modePrms->m_autfgp = m_sev->genCmdReadAutoTurnningFgp(axisInx, ok);
          ui->label_mode_aut_fgp->setText(QString::number(modePrms->m_autfgp));
          modePrms->m_autfgi = m_sev->genCmdReadAutoTurnningFgi(axisInx, ok);
          ui->label_mode_aut_fgi->setText(QString::number(modePrms->m_autfgi));
          modePrms->m_autfgn = m_sev->genCmdReadAutoTurnningFgn(axisInx, ok);
          ui->label_mode_aut_fgn->setText(QString::number(modePrms->m_autfgn));

          ui->doubleSpinBox_mode_autAcc->setStyleSheet("color:black");
          ui->doubleSpinBox_mode_autDec->setStyleSheet("color:black");
          ui->doubleSpinBox_mode_autMaxVel->setStyleSheet("color:black");
          ui->doubleSpinBox_mode_aut_pulse->setStyleSheet("color:black");
      }
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}

void TabModeCtl::onCssChanged(const QString &css)
{
  setupIcons(css);
}
void TabModeCtl::onModeSpinBoxValueChanged(int value)
{
  Q_UNUSED(value);
  QSpinBox *box = qobject_cast<QSpinBox *>(sender());
  box->setStyleSheet("color:red");
}

void TabModeCtl::onModeDoubleSpinBoxValueChanged(double value)
{
    Q_UNUSED(value);
    QDoubleSpinBox *box = qobject_cast<QDoubleSpinBox *>(sender());
    box->setStyleSheet("color:red");
}
void TabModeCtl::onModeCtlPanelModeChanged(quint16 axis, int mode)
{
  if(mode == -1)
    return ;
  qDebug()<<axis<<mode;
  if(mode<ui->stackedWidget_plot_mode->count())
  {
    m_currenAxis=axis;
    ModeCtlPrms* modePrms=m_dataList.at(axis);
    modePrms->m_curMode=(GT::ModeCtlType)mode;
    ui->stackedWidget_plot_mode->setCurrentIndex(mode);
    m_sev->setCurrentTaskServoMode(axis,mode);//下发实际指令
    switch(mode)
    {
    case GT::MODE_IDLE:break;
    case GT::MODE_ADC:break;
    case GT::MODE_IPA:
    {
      ui->spinBox_mode_ipa->setValue(modePrms->m_ipa);
      ui->spinBox_mode_ipa->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_MPI:break;
    case GT::MODE_COL:
    {
      ui->spinBox_mode_uaref->setValue(modePrms->m_uaref);
      ui->spinBox_mode_ubref->setValue(modePrms->m_ubref);
      ui->spinBox_mode_ucref->setValue(modePrms->m_ucref);
      ui->spinBox_mode_udref->setValue(modePrms->m_udref);
      ui->spinBox_mode_uqref->setValue(modePrms->m_uqref);

      ui->spinBox_mode_uaref->setStyleSheet("color:black");
      ui->spinBox_mode_ubref->setStyleSheet("color:black");
      ui->spinBox_mode_ucref->setStyleSheet("color:black");
      ui->spinBox_mode_udref->setStyleSheet("color:black");
      ui->spinBox_mode_uqref->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_CCL:
    {
      ui->spinBox_mode_idref->setValue(modePrms->m_idref);
      ui->spinBox_mode_iqref->setValue(modePrms->m_iqref);

      ui->spinBox_mode_idref->setStyleSheet("color:black");
      ui->spinBox_mode_iqref->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_VCL:
    {
      ui->spinBox_mode_vcl->setValue(modePrms->m_vcl);
      ui->spinBox_mode_vcl->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_VPL:
    {
      ui->spinBox_mode_vpl->setValue(modePrms->m_vpl);
      ui->spinBox_mode_vpl->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_VSL:
    {
      ui->spinBox_mode_vsl->setValue(modePrms->m_vsl);
      ui->spinBox_mode_vsl->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_FIX:break;
    case GT::MODE_PT:
    {
      ui->spinBox_mode_pt->setValue(modePrms->m_pt);
      ui->spinBox_mode_pt->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_DB:break;
    case GT::MODE_CSC:break;
    case GT::MODE_AUT:
    {
        if (m_sev->isConnecting()) {
            bool ok;
            quint64 nos = m_sev->genCmdReadNos(axis, ok);
            double scale = nos / (pow(2, 24));
            modePrms->m_autAcc = m_sev->genCmdRead(GEN_CMD_ACC, axis, ok);
            ui->doubleSpinBox_mode_autAcc->setValue(modePrms->m_autAcc);
            modePrms->m_autDec = m_sev->genCmdRead(GEN_CMD_DEC, axis, ok);
            ui->doubleSpinBox_mode_autDec->setValue(modePrms->m_autDec);
            modePrms->m_autVel = m_sev->genCmdRead(GEN_CMD_MAXVEL, axis, ok) * scale;
            ui->doubleSpinBox_mode_autMaxVel->setValue(modePrms->m_autVel);
            m_sev->genCmdWritePlanSpdAcc(axis, modePrms->m_autAcc);
            m_sev->genCmdWritePlanSpdDec(axis, modePrms->m_autDec);
            m_sev->genCmdWritePlanSpdMax(axis, modePrms->m_autVel);
            m_sev->cmdSetPosRef(axis, modePrms->m_autPulse);

            modePrms->m_autfgd = m_sev->genCmdReadAutoTurnningFgd(axis, ok);
            ui->label_mode_aut_fgd->setText(QString::number(modePrms->m_autfgd));
            modePrms->m_autfgp = m_sev->genCmdReadAutoTurnningFgp(axis, ok);
            ui->label_mode_aut_fgp->setText(QString::number(modePrms->m_autfgp));
            modePrms->m_autfgi = m_sev->genCmdReadAutoTurnningFgi(axis, ok);
            ui->label_mode_aut_fgi->setText(QString::number(modePrms->m_autfgi));
            modePrms->m_autfgn = m_sev->genCmdReadAutoTurnningFgn(axis, ok);
            ui->label_mode_aut_fgn->setText(QString::number(modePrms->m_autfgn));

        }
        ui->doubleSpinBox_mode_aut_pulse->setValue(modePrms->m_autPulse);
        ui->label_mode_aut_fgd->setText(QString::number(modePrms->m_autfgd));
        ui->label_mode_aut_fgp->setText(QString::number(modePrms->m_autfgp));
        ui->label_mode_aut_fgi->setText(QString::number(modePrms->m_autfgi));
        ui->label_mode_aut_fgn->setText(QString::number(modePrms->m_autfgn));
        ui->doubleSpinBox_mode_autAcc->setValue(modePrms->m_autAcc);
        ui->doubleSpinBox_mode_autDec->setValue(modePrms->m_autDec);
        ui->doubleSpinBox_mode_autMaxVel->setValue(modePrms->m_autVel);

        ui->doubleSpinBox_mode_aut_pulse->setStyleSheet("color:black");
        ui->label_mode_aut_fgd->setStyleSheet("color:black");
        ui->label_mode_aut_fgi->setStyleSheet("color:black");
        ui->label_mode_aut_fgn->setStyleSheet("color:black");
        ui->label_mode_aut_fgp->setStyleSheet("color:black");
        ui->doubleSpinBox_mode_autAcc->setStyleSheet("color:black");
        ui->doubleSpinBox_mode_autDec->setStyleSheet("color:black");
        ui->doubleSpinBox_mode_autMaxVel->setStyleSheet("color:black");
    }
    break;
    }
  }
}
void TabModeCtl::onModeCtlPanelCheckChanged(quint16 axis, int mode)
{
  qDebug()<<axis<<mode;
  //还原对应轴的参数设置
  if(mode<ui->stackedWidget_plot_mode->count())
  {
    m_currenAxis=axis;
    ModeCtlPrms* modePrms=m_dataList.at(axis);
    modePrms->m_curMode=(GT::ModeCtlType)mode;
    ui->stackedWidget_plot_mode->setCurrentIndex(mode);
    switch(mode)
    {
    case GT::MODE_IDLE:break;
    case GT::MODE_ADC:break;
    case GT::MODE_IPA:
    {
      ui->spinBox_mode_ipa->setValue(modePrms->m_ipa);
      ui->spinBox_mode_ipa->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_MPI:break;
    case GT::MODE_COL:
    {
      ui->spinBox_mode_uaref->setValue(modePrms->m_uaref);
      ui->spinBox_mode_ubref->setValue(modePrms->m_ubref);
      ui->spinBox_mode_ucref->setValue(modePrms->m_ucref);
      ui->spinBox_mode_udref->setValue(modePrms->m_udref);
      ui->spinBox_mode_uqref->setValue(modePrms->m_uqref);

      ui->spinBox_mode_uaref->setStyleSheet("color:black");
      ui->spinBox_mode_ubref->setStyleSheet("color:black");
      ui->spinBox_mode_ucref->setStyleSheet("color:black");
      ui->spinBox_mode_udref->setStyleSheet("color:black");
      ui->spinBox_mode_uqref->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_CCL:
    {
      ui->spinBox_mode_idref->setValue(modePrms->m_idref);
      ui->spinBox_mode_iqref->setValue(modePrms->m_iqref);

      ui->spinBox_mode_idref->setStyleSheet("color:black");
      ui->spinBox_mode_iqref->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_VCL:
    {
      ui->spinBox_mode_vcl->setValue(modePrms->m_vcl);
      ui->spinBox_mode_vcl->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_VPL:
    {
      ui->spinBox_mode_vpl->setValue(modePrms->m_vpl);
      ui->spinBox_mode_vpl->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_VSL:
    {
      ui->spinBox_mode_vsl->setValue(modePrms->m_vsl);
      ui->spinBox_mode_vsl->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_FIX:break;
    case GT::MODE_PT:
    {
      ui->spinBox_mode_pt->setValue(modePrms->m_pt);
      ui->spinBox_mode_pt->setStyleSheet("color:black");
    }
    break;
    case GT::MODE_DB:break;
    case GT::MODE_CSC:break;
    case GT::MODE_AUT:
    {
        ui->doubleSpinBox_mode_aut_pulse->setValue(modePrms->m_autPulse);
        ui->label_mode_aut_fgd->setText(QString::number(modePrms->m_autfgd));
        ui->label_mode_aut_fgp->setText(QString::number(modePrms->m_autfgp));
        ui->label_mode_aut_fgi->setText(QString::number(modePrms->m_autfgi));
        ui->label_mode_aut_fgn->setText(QString::number(modePrms->m_autfgn));
        ui->doubleSpinBox_mode_autAcc->setValue(modePrms->m_autAcc);
        ui->doubleSpinBox_mode_autDec->setValue(modePrms->m_autDec);
        ui->doubleSpinBox_mode_autMaxVel->setValue(modePrms->m_autVel);

        ui->doubleSpinBox_mode_aut_pulse->setStyleSheet("color:black");
        ui->label_mode_aut_fgd->setStyleSheet("color:black");
        ui->label_mode_aut_fgi->setStyleSheet("color:black");
        ui->label_mode_aut_fgn->setStyleSheet("color:black");
        ui->label_mode_aut_fgp->setStyleSheet("color:black");
        ui->doubleSpinBox_mode_autAcc->setStyleSheet("color:black");
        ui->doubleSpinBox_mode_autDec->setStyleSheet("color:black");
        ui->doubleSpinBox_mode_autMaxVel->setStyleSheet("color:black");
    }
    break;
    }
  }
}

void TabModeCtl::onBtnServoOnClicked(bool checked)
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
      ui->label_plot_servo_onoff->setText(tr("SEV ON"));
      qDebug()<<"setServoOn "<<i<<checked;
      qDebug()<<"----------sev axis is on"<<m_sev->axisServoIsOn(i)<<"-----------";
    }
  }
}
