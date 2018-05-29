#include "velplanmotion.h"
#include "uimotionvelocity.h"
#include "sevdevice.h"
#include "gtutils.h"
#include <QDebug>

VelPlanMotion::VelPlanMotion(quint16 axisInx,SevDevice *dev,UiMotionData * data,QObject *parent) : QObject(parent),
  m_sev(dev),
  m_data(data),
  m_axisInx(axisInx)
{
  m_timer.setTimerType(Qt::PreciseTimer);
  connect(&m_timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
}

VelPlanMotion::~VelPlanMotion()
{

}

QTimer *VelPlanMotion::timer()
{
  return &m_timer;
}

void VelPlanMotion::movePrepare()
{
  m_sev->cmdSetSpdRef(m_axisInx,0);
  m_sev->cmdSetSpdRef(m_axisInx,0);
  m_sev->setCurrentTaskServoMode(m_axisInx,GT::MODE_VCL);
  m_sev->setCurrentTaskServoMode(m_axisInx,GT::MODE_VCL);
  m_sev->setAxisServoOn(m_axisInx,true);

  m_data->m_curTimeout = 0;
  m_data->m_seqCircleUse = 0;
  m_data->m_stepCircleUse = 0;
  m_data->m_breakByHand = false;
  m_data->m_runSta = UiMotionData::RUN_STA_RUNNING;

  //计算进度条相关
  if(m_data->m_isCircle)
  {
    m_data->m_seqInc = 100.0/(m_data->m_seqCircleCount*2);
    m_timer.setInterval(m_data->m_seqPeriod/2);
  }
  else
  {
    //每200ms更新一次
    quint32 time = m_data->m_stepTime*1000;
    m_data->m_stepCircleCount = time/200;
    m_data->m_stepInc = 100.0/m_data->m_stepCircleCount;
    m_timer.setInterval(200);
  }
  qDebug()<<"seqInc"<<m_data->m_seqInc<<"stepInc"<<m_data->m_stepInc<<"stepCircleCount"<<m_data->m_stepCircleCount;
}

void VelPlanMotion::move()
{
  if(m_data->m_isCircle)
  {
    m_sev->cmdSetSpdRef(m_axisInx,m_data->m_seqAmp);
  }
  else
  {
    m_sev->cmdSetSpdRef(m_axisInx,m_data->m_stepAmp);
  }
  m_timer.start();
  qDebug()<<"move timer start";
}

void VelPlanMotion::stop()
{
  qDebug()<<"VelPlanMotion stop";
  m_data->m_breakByHand = true;
}

void VelPlanMotion::onTimerOut()
{
  if(m_data->m_isCircle)
  {
    m_data->m_seqCircleUse ++;
    if((m_data->m_seqCircleUse >= m_data->m_seqCircleCount*2)||(m_data->m_breakByHand == true))
      m_data->m_runSta = UiMotionData::RUN_STA_STOPING;
  }
  else
  {
    m_data->m_stepCircleUse ++;
    emit progressValueChanged(m_axisInx,m_data->m_stepInc*m_data->m_stepCircleUse);
    if((m_data->m_stepCircleUse >= m_data->m_stepCircleCount)||(m_data->m_breakByHand == true))
    {
      m_data->m_runSta = UiMotionData::RUN_STA_STOPING;
    }
  }

  switch (m_data->m_runSta)
  {
  case UiMotionData::RUN_STA_RUNNING:
    if(m_data->m_isCircle)
    {
      m_data->m_switch = !m_data->m_switch;
      if(m_data->m_switch)
        m_sev->cmdSetSpdRef(m_axisInx,m_data->m_seqAmp);
      else
        m_sev->cmdSetSpdRef(m_axisInx,-1*m_data->m_seqAmp);

      qDebug()<<"circle timer out"<<"RUN_STA_RUNNING"<<"switch "<<m_data->m_switch;
    }
    break;

  case UiMotionData::RUN_STA_STOPING:
  {
    double value = 0;
    m_sev->cmdSetSpdRef(m_axisInx,0);
    value = m_sev->cmdGetSpdFb(m_axisInx,value);
    m_data->m_curTimeout ++;
    if(((value>m_data->m_velranglow)&&(value<m_data->m_velrangUp))||(m_data->m_curTimeout>m_data->m_timeoutMaxCount))
    {
      m_sev->setAxisServoOn(m_axisInx,false);
      m_timer.stop();
      emit motionFinish(m_axisInx);
      qDebug()<<"circle timer stop !!!!!!!!!!!!!!!!!!!!";
    }
    qDebug()<<"circle timer out"<<"RUN_STA_STOPING"<<"m_curTimeout "<<m_data->m_curTimeout<<"value = "<<value;
  }
    break;
  }
  int pvalue = 0;
  if(m_data->m_isCircle)
    pvalue = m_data->m_seqInc*m_data->m_seqCircleUse;
  else
    pvalue = m_data->m_stepInc*m_data->m_stepCircleUse;

  emit progressValueChanged(m_axisInx,pvalue);
}

