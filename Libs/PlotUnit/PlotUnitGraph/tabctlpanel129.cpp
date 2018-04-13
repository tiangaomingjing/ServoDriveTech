#include "tabctlpanel129.h"
#include "ui_tabctlpanel129.h"
#include "sevdevice.h"

#include <QDebug>
#include <QKeyEvent>

TabCtlPanel129::TabCtlPanel129(SevDevice *sev, QWidget *parent) : QWidget(parent),
  ui(new Ui::TabCtlPanel129),
  m_sev(sev)
{
  ui->setupUi(this);
  m_data=new PlotTabCtlPrms(sev->axisNum());
  ui->modeCtlPanel->setAxis(sev->axisNum());

  //tab mode
  connect(ui->modeCtlPanel,SIGNAL(checkChanged(quint16,int)),this,SLOT(onModeCtlPanelCheckChanged(quint16,int)));
  connect(ui->modeCtlPanel,SIGNAL(modeChanged(quint16,int)),this,SLOT(onModeCtlPanelModeChanged(quint16,int)));
  //tab motion
}

TabCtlPanel129::~TabCtlPanel129()
{
  delete m_data;
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
      qDebug()<<"spinBox value"<<box->value();
      if(obj==ui->spinBox_mode_ipa)//3 初始化相位
      {
        modePrms->m_ipa=ui->spinBox_mode_ipa->value();
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
      }
      else if(obj==ui->spinBox_mode_idref||obj==ui->spinBox_mode_iqref)   //5 电流闭环调试
      {
        modePrms->m_idref=ui->spinBox_mode_idref->value();
        modePrms->m_iqref=ui->spinBox_mode_iqref->value();
      }
      else if(obj==ui->spinBox_mode_vcl)                                  //6 速度闭环调试
      {
        modePrms->m_vcl=ui->spinBox_mode_vcl->value();
      }
      else if(obj==ui->spinBox_mode_vpl)                                  //7 轮廓速度跟踪
      {
        modePrms->m_vpl=ui->spinBox_mode_vpl->value();
      }
      else if(obj==ui->spinBox_mode_vsl)                                  //8 周期同步速度跟踪
      {
        modePrms->m_vsl=ui->spinBox_mode_vsl->value();
      }
      else if(obj==ui->spinBox_mode_pt)                                  //8 周期同步位置跟踪
      {
        modePrms->m_pt=ui->spinBox_mode_pt->value();
      }
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}

void TabCtlPanel129::onModeCtlPanelCheckChanged(quint16 axis, int mode)
{
  qDebug()<<axis<<mode;
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

