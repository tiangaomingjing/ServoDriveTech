#include "nolinearautoturning.h"
#include "sevdevice.h"
#include "gtutils.h"

#include <QTimer>

NolinearAutoTurning::NolinearAutoTurning(SevDevice *sev, quint16 axisInx, QObject *parent) : QObject(parent),
  m_sev(sev),
  m_axisInx(axisInx),
  m_acc(0),
  m_dec(0),
  m_maxSpd(0),
  m_pulseNum(0),
  m_waitCount(0),
  m_waitMaxCount(200),
  m_progressValue(0)
{
  m_timer = new QTimer(this);
  m_timer->setInterval(100);
  connect(m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
  connect(m_sev,SIGNAL(netError(quint16)),this,SLOT(onSevDeviceNetError(quint16)));
}

NolinearAutoTurning::~NolinearAutoTurning()
{

}

qreal NolinearAutoTurning::acc() const
{
  return m_acc;
}

void NolinearAutoTurning::setAcc(qreal acc)
{
  m_acc = acc;
}

qreal NolinearAutoTurning::dec() const
{
  return m_dec;
}

void NolinearAutoTurning::setDec(qreal dec)
{
  m_dec = dec;
}

qreal NolinearAutoTurning::maxSpd() const
{
  return m_maxSpd;
}

void NolinearAutoTurning::setMaxSpd(qreal maxSpd)
{
  m_maxSpd = maxSpd;
}

qreal NolinearAutoTurning::pulseNum() const
{
  return m_pulseNum;
}

void NolinearAutoTurning::setPulseNum(qreal pulseNum)
{
  m_pulseNum = pulseNum;
}

void NolinearAutoTurning::recoverStatus()
{
  if(m_sev->isConnecting())
  {
    m_sev->setAxisServoOn(m_axisInx,false);
    m_sev->setAxisServoOn(m_axisInx,false);
    m_sev->setControlSrc(m_axisInx,m_prevSrc);
    m_sev->setCurrentTaskServoMode(m_axisInx,m_prevMode);

  }
}

void NolinearAutoTurning::onTimeOut()
{
  m_progressValue ++;
  m_waitCount ++;
  if(m_progressValue == 100)
    m_progressValue = 0;
  emit progressChanged(m_progressValue);

  bool isOk = false;
  bool finish = false;
  finish = m_sev->genCmdAutoTurnningFinishFlag(m_axisInx,isOk);
  if((finish == true))
  {
    emit autoTurnigFinish(true);

    stop();
  }
  if(m_waitCount>m_waitMaxCount)
  {
    autoTurnigFinish(false);

    stop();
  }
}

void NolinearAutoTurning::onSevDeviceNetError(quint16 axisInx)
{
  if(axisInx ==  m_axisInx)
  {
    stop();
  }
}

quint16 NolinearAutoTurning::waitMaxCount() const
{
  return m_waitMaxCount;
}

void NolinearAutoTurning::setWaitMaxCount(quint16 waitMaxCount)
{
  m_waitMaxCount = waitMaxCount;
}

quint64 NolinearAutoTurning::autoTnFgd(int axisInx)
{
  bool isOk ;
  return m_sev->genCmdReadAutoTurnningFgd(axisInx,isOk);
}

quint64 NolinearAutoTurning::autoTnFgp(int axisInx)
{
  bool isOk ;
  return m_sev->genCmdReadAutoTurnningFgp(axisInx,isOk);
}

quint64 NolinearAutoTurning::autoTnFgi(int axisInx)
{
  bool isOk ;
  return m_sev->genCmdReadAutoTurnningFgi(axisInx,isOk);
}

quint64 NolinearAutoTurning::autoTnFgn(int axisInx)
{
  bool isOk ;
  return m_sev->genCmdReadAutoTurnningFgn(axisInx,isOk);
}

bool NolinearAutoTurning::start()
{
//  if(!m_sev->isConnecting())
//    return true;
  m_prevMode = (GT::ModeCtlType)m_sev->currentTaskServoMode(m_axisInx);
  m_prevSrc = m_sev->controlSrc(m_axisInx);
  m_sev->cmdSetPosRef(m_axisInx,0);
  m_sev->cmdSetPosRef(m_axisInx,0);

  //获取控制权
  bool getControl = false;
  for(int i=0;i<100;i++)
  {
    m_sev->setControlSrc(m_axisInx,GT::SEV_CTL_SRC_PC);
    GTUtils::delayms(10);
    if(GT::SEV_CTL_SRC_PC == m_sev->controlSrc(m_axisInx))
    {
      getControl = true;
      break;
    }
  }
  if(!getControl)
  {
    recoverStatus();
    return false;
  }

  //设置AUT模式
  bool modeOk = false;
  for(int i=0;i<100;i++)
  {
    m_sev->setCurrentTaskServoMode(m_axisInx,GT::MODE_AUT);
    GTUtils::delayms(10);
    if(GT::MODE_AUT == m_sev->currentTaskServoMode(m_axisInx))
    {
      modeOk = true;
      break;
    }
  }
  if(!modeOk)
  {
    recoverStatus();
    return false;
  }


  if(!m_sev->genCmdWritePlanSpdAcc(m_axisInx,m_acc))
    m_sev->genCmdWritePlanSpdAcc(m_axisInx,m_acc);
  if(!m_sev->genCmdWritePlanSpdDec(m_axisInx,m_dec))
    m_sev->genCmdWritePlanSpdDec(m_axisInx,m_dec);
  if(!m_sev->genCmdWritePlanSpdMax(m_axisInx,m_maxSpd))
    m_sev->genCmdWritePlanSpdMax(m_axisInx,m_maxSpd);
  m_sev->cmdSetPosRef(m_axisInx,m_pulseNum);
  m_sev->cmdSetPosRef(m_axisInx,m_pulseNum);

  //上伺服
  bool servoIsOn = false;
  for(int count = 0;count<100;count++)
  {
    m_sev->setAxisServoOn(m_axisInx,true);
    GTUtils::delayms(10);
    servoIsOn = m_sev->axisServoIsOn(m_axisInx);
    if(servoIsOn)
    {
      break;
    }

  }

  if(!servoIsOn)
  {
    recoverStatus();
    return false;
  }

  m_timer->start();

  return true;
}

void NolinearAutoTurning::stop()
{
  m_progressValue = 0;
  m_waitCount = 0;
  m_timer->stop();
  recoverStatus();
}


