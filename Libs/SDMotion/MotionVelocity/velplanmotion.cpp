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

  int tryCount = 1000;
  int tryUse = 0;
  bool isOn = false;
  do
  {
    m_sev->setCurrentTaskServoMode(m_axisInx,GT::MODE_VCL);
    m_sev->setAxisServoOn(m_axisInx,true);
    isOn = m_sev->axisServoIsOn(m_axisInx);
    GTUtils::delayms(1);
    tryUse ++;
  }while((isOn == false)&&(tryUse < tryCount));

  qDebug()<<"--------------axis = "<<m_axisInx<<"mode = "<<m_sev->currentTaskServoMode(m_axisInx)<<"isOn"<<isOn<<"tryUse = "<<tryUse;

  m_data->m_curTimeout = 0;
  m_data->m_seqCircleUse = 0;
  m_data->m_stepCircleUse = 0;
  m_data->m_breakByHand = false;
  m_data->m_switch = false;
  m_data->m_runSta = UiMotionData::RUN_STA_INIT;

  //计算进度条相关
  if(m_data->m_isCircle)
  {
    m_data->m_seqInc = 100.0/(m_data->m_seqCircleCount*2);
    double inc = m_data->m_seqPeriod/2.0;
    m_timer.setInterval(inc);
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
  m_timer.start();
//  if(m_data->m_isCircle)
//  {
//    m_sev->cmdSetSpdRef(m_axisInx,m_data->m_seqAmp);
//  }
//  else
//  {
//    m_sev->cmdSetSpdRef(m_axisInx,m_data->m_stepAmp);
//  }

}

void VelPlanMotion::stop()
{
  qDebug()<<"VelPlanMotion stop";
  m_data->m_breakByHand = true;
}

void VelPlanMotion::onTimerOut()
{
//  static int testCount = 0;
//  testCount ++;
  if(m_data->m_isCircle)
  {
    m_data->m_seqCircleUse ++;
    if((m_data->m_seqCircleUse >= m_data->m_seqCircleCount*2)||(m_data->m_breakByHand == true))
    {
      m_sev->cmdSetSpdRef(m_axisInx,0);
      m_data->m_runSta = UiMotionData::RUN_STA_STOPING;
    }
  }
  else
  {
    m_data->m_stepCircleUse ++;
    emit progressValueChanged(m_axisInx,m_data->m_stepInc*m_data->m_stepCircleUse);
    if((m_data->m_stepCircleUse >= m_data->m_stepCircleCount)||(m_data->m_breakByHand == true))
    {
      m_sev->cmdSetSpdRef(m_axisInx,0);
      m_data->m_runSta = UiMotionData::RUN_STA_STOPING;
    }
  }

  switch (m_data->m_runSta)
  {
  case UiMotionData::RUN_STA_INIT:
    if(!m_data->m_isCircle)
    {
      m_sev->cmdSetSpdRef(m_axisInx,m_data->m_stepAmp);
    }
//    qDebug()<<"run sta = "<<" RUN_STA_INIT";
    m_data->m_runSta = UiMotionData::RUN_STA_RUNNING;
  case UiMotionData::RUN_STA_RUNNING:
    if(m_data->m_isCircle)
    {
      m_data->m_switch = !m_data->m_switch;
      if(m_data->m_switch)
        m_sev->cmdSetSpdRef(m_axisInx,m_data->m_seqAmp);
      else
        m_sev->cmdSetSpdRef(m_axisInx,-1*m_data->m_seqAmp);

//      qDebug()<<"circle timer out"<<"RUN_STA_RUNNING"<<"switch = "<<m_data->m_switch;
    }
    break;

  case UiMotionData::RUN_STA_STOPING:
  {
    double value = 0;
    m_sev->cmdSetSpdRef(m_axisInx,0);
    m_sev->cmdGetSpdFbPercent(m_axisInx,value);
    m_data->m_curTimeout ++;
//    qDebug()<<"RUN_STA_STOPING"<<"m_curTimeout "<<m_data->m_curTimeout<<"value = "<<value;

    if(((value>m_data->m_velranglow)&&(value<m_data->m_velrangUp))||(m_data->m_curTimeout>m_data->m_timeoutMaxCount))
    {
      m_sev->cmdSetSpdRef(m_axisInx,0);
      qDebug()<<"circle timer stop !!!!!!!!!!!!!!!!!!!!"<<" value = "<<value;
      m_timer.stop();
      GTUtils::delayms(10);
      m_sev->setAxisServoOn(m_axisInx,false);
      emit motionFinish(m_axisInx);

    }

  }
    break;
  }

//  double value = 0;
//  m_sev->cmdGetSpdFbPercent(m_axisInx,value);
//  qDebug()<<"spd value = "<<value<<" testCount = "<<testCount;

  int pvalue = 0;
  if(m_data->m_isCircle)
    pvalue = m_data->m_seqInc*m_data->m_seqCircleUse;
  else
    pvalue = m_data->m_stepInc*m_data->m_stepCircleUse;

  emit progressValueChanged(m_axisInx,pvalue);
}

