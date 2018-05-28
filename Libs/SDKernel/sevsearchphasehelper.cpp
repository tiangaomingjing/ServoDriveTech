#include "sevsearchphasehelper.h"
#include "sevdevice.h"
#include <QDebug>

#define KEY_IPA_FINISH_FLAG "gSevDrv.sev_obj.mfj.pos_adj_flag"

#define TIME_INTERVAL 100
#define MAX_CHECK_FINISH_TIMEOUT_SIZE 50
#define MAX_SEV_OFF_TIMEOUT_SIZE 3
#define MAX_TRY_SET_CTLSRC_SIZE 3

SevSearchPhaseHelper::SevSearchPhaseHelper(SevDevice *sev, quint16 axisInx, QObject *parent) : QObject(parent),
  m_sev(sev),
  m_axisInx(axisInx),
  m_curControlSrc(GT::SEV_CTL_SRC_GLINK2),
  m_sta(IPA_STA_CHECK_SEVON),
  m_checkSevOnCountUse(0)
{
  m_timer.setInterval(TIME_INTERVAL);
  connect(&m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
}

SevSearchPhaseHelper::~SevSearchPhaseHelper()
{
  if(m_timer.isActive())
    m_timer.stop();
}

bool SevSearchPhaseHelper::searchPhaseStart(int value)
{
  qDebug()<<"SevSearchPhaseHelper::searchPhaseStart(int value) axisInx = "<<m_axisInx;
  m_checkSevOnCountUse = 0 ;
  m_checkFinishCountUse = 0 ;
  m_progressValue = 0;
  m_sta = IPA_STA_CHECK_SEVON;

  bool on = m_sev->axisServoIsOn(m_axisInx);
  if(on)
  {
    emit ipaWarningMsg(tr("Servo is on now ! refuse to search phase !"));
    return false;
  }

  m_curControlSrc = m_sev->controlSrc(m_axisInx);//先保存当前的控制权

  int tryCount = 0;
  GT::SevControlSrc src = GT::SEV_CTL_SRC_GLINK2;
  do{
    src = m_sev->controlSrc(m_axisInx);
    if(src != GT::SEV_CTL_SRC_PC)
      m_sev->setControlSrc(m_axisInx,GT::SEV_CTL_SRC_PC);
    tryCount++;
    qDebug()<<"tryCount "<<tryCount;
  }while((src != GT::SEV_CTL_SRC_PC)&&(tryCount<MAX_TRY_SET_CTLSRC_SIZE));

  qDebug()<<"control src = "<<src;
  if(tryCount>=MAX_TRY_SET_CTLSRC_SIZE)
  {
    qDebug()<<"emit ipaWarningMsg  can not get the pc control source ";
    emit ipaWarningMsg(tr("can not get the pc control source !"));
    return false ;
  }

  m_curMode = (GT::ModeCtlType)m_sev->currentTaskServoMode(m_axisInx);


  m_sev->setCurrentTaskServoMode(m_axisInx,GT::MODE_IPA);
  if(GT::MODE_IPA != m_sev->currentTaskServoMode(m_axisInx))
    m_sev->setCurrentTaskServoMode(m_axisInx,GT::MODE_IPA);

  GT::ModeCtlType modeType = (GT::ModeCtlType)m_sev->currentTaskServoMode(m_axisInx);

  if(GT::MODE_IPA != modeType)
  {
    qDebug()<<"can not set mode initial phase";
    emit ipaWarningMsg(tr("can not set mode initial phase !"));
    return false ;
  }

  m_sev->cmdSetPosAdjRef(m_axisInx,value);
  m_sev->cmdSetPosAdjRef(m_axisInx,value);

  m_sev->setAxisServoOn(m_axisInx,true);

  m_timer.start();
  qDebug()<<"m_timer.start";
  return true;
}

void SevSearchPhaseHelper::onTimeOut()
{
  m_progressValue += 10;
  if(m_progressValue >=100)
    m_progressValue = 0;

  switch (m_sta)
  {
  case IPA_STA_CHECK_SEVON:
  {
    bool isOn = false;

    m_checkSevOnCountUse ++;

    isOn = m_sev->axisServoIsOn(m_axisInx);

    if(!isOn)
    {
      m_sev->setControlSrc(m_axisInx,GT::SEV_CTL_SRC_PC);
      m_sev->setAxisServoOn(m_axisInx,true);
    }
    else
    {
      m_sta = IPA_STA_CHECK_FINISH;
    }

    if((m_checkSevOnCountUse >= MAX_SEV_OFF_TIMEOUT_SIZE)&&(isOn == false))
    {
      emit ipaWarningMsg(tr("can not set axis on !"));
      m_sta = IPA_STA_DONE;
    }

    emit ipaSearchPhaseInfo(m_progressValue,tr("servo is on checking......"));
  }
    break;

  case IPA_STA_CHECK_FINISH:
  {
    bool finish = checkIpaFinishFlag();
    if(finish || (m_checkFinishCountUse > MAX_CHECK_FINISH_TIMEOUT_SIZE))
      m_sta = IPA_STA_DONE;
    m_checkFinishCountUse ++;
    emit ipaSearchPhaseInfo(m_progressValue,tr("ipa finish flag is ture checking......"));
  }
    break;

  case IPA_STA_DONE:
  {
    m_timer.stop();
    m_sev->setAxisServoOn(m_axisInx,false);
    m_sev->setControlSrc(m_axisInx,m_curControlSrc);
    m_sev->setCurrentTaskServoMode(m_axisInx,m_curMode);
    m_sev->cmdSetPosAdjRef(m_axisInx,0);
    m_progressValue = 0 ;
    emit ipaDone();
  }
    break;
  }
}

bool SevSearchPhaseHelper::checkIpaFinishFlag()
{
  bool isOk = true;
  int ret = m_sev->genCmdRead(KEY_IPA_FINISH_FLAG,m_axisInx,isOk);
  if(!isOk)
    return false;
  return ret == 1;
}

