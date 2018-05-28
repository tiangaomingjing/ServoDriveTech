#include "vmotionthread.h"
#include "uimotionvelocity.h"
#include "sevdevice.h"
#include "Option"
#include "sdtglobaldef.h"

#include <QDebug>
#define MIN_PERIOD 10

VmotionThread::VmotionThread(SevDevice *dev, QList<UiMotionData *> dataList, QObject *parent) : QThread(parent),
  m_motionDataList(dataList),
  m_sev(dev)
{

}

VmotionThread::~VmotionThread()
{
  if(isRunning())
    stop();
  quit();
  wait();
}

void VmotionThread::setSevDevice(SevDevice *dev)
{
  m_sev = dev;
}

void VmotionThread::setUiMotionData(QList<UiMotionData *> data)
{
  m_motionDataList = data;
}

void VmotionThread::stop()
{
  m_bRun = false;
}

quint16 VmotionThread::msdelayTime()
{
  quint16 t = MIN_PERIOD;
  return t;
}

void VmotionThread::run()
{
  //init
  while (m_bRun)
  {
    for(int i=0;i<m_motionDataList.size();i++)
    {
      quint16 axis = i;
      UiMotionData *data = m_motionDataList.at(i);
      bool start = false;
      data->m_lock.lockForRead();
      start = data->m_start;
      data->m_lock.unlock();

      if(start)
      {
        UiMotionData::MotionRunSta sta;
        data->m_lock.lockForRead();
        sta = data->m_runSta;
        data->m_lock.unlock();
        switch (sta)
        {
        case UiMotionData::RUN_STA_INIT:
          m_sev->cmdSetSpdRef(axis,0);
          m_sev->setCurrentTaskServoMode(axis,GT::MODE_VCL);
          m_sev->setAxisServoOn(axis,true);

          data->m_lock.lockForWrite();
          data->m_runSta = UiMotionData::RUN_STA_CHECK_ON;
          data->m_lock.unlock();
          qDebug()<<"axis = "<<axis<<"cur sta = RUN_STA_INIT";
          break;
        case UiMotionData::RUN_STA_CHECK_ON:
          {
            bool on = true;
            on = m_sev->axisServoIsOn(axis);
            data->m_lock.lockForWrite();
            data->m_currentCount ++;

            if((!on)&&(data->m_currentCount >10) )
            {
              data->m_runSta = UiMotionData::RUN_STA_STOP_FINISH;
            }
            else
            {
              if(data->m_currentCount >= data->m_delayStartCount)
              {
                data->m_runSta = UiMotionData::RUN_STA_RUNNING;
              }

            }
            data->m_lock.unlock();
            qDebug()<<"axis = "<<axis<<"cur sta = RUN_STA_CHECK_ON "<<on<<"count "<<data->m_currentCount<<"delay count"<<data->m_delayStartCount;
          }
          break;
        case UiMotionData::RUN_STA_RUNNING:
          data->m_lock.lockForWrite();

          if(data->m_isCircle)
          {
            quint8 yuShu = (data->m_seqPeriod/2)%MIN_PERIOD;
            if(((data->m_currentCount*MIN_PERIOD)%(data->m_seqPeriod/2 -yuShu)) ==0)
            {
              if(data->m_switch)
              {
                m_sev->cmdSetSpdRef(axis,data->m_seqAmp);
              }
              else
              {
                m_sev->cmdSetSpdRef(axis,-1*data->m_seqAmp);
              }
              data->m_switch = !data->m_switch;
              data->m_seqCircleUse ++;
            }
            qDebug()<<"axis = "<<axis<<"seq circle use = "<<data->m_seqCircleUse\
                   <<"circle count = "<<data->m_seqCircleCount\
                   <<"sw = "<<data->m_switch\
                   <<"period = "<<data->m_seqPeriod<<"cur sta = RUN_STA_RUNNING "<<"count"<<data->m_currentCount;

            if(data->m_seqCircleUse > data->m_seqCircleCount)
              data->m_runSta = UiMotionData::RUN_STA_STOPING;

          }
          else
          {
            if(data->m_stepIsSetOn == false)
            {
              m_sev->cmdSetSpdRef(axis,data->m_stepAmp);
              data->m_stepIsSetOn = true;
            }
            quint32 time=(data->m_stepTime*1000);
            if((data->m_currentCount*MIN_PERIOD) >= time)
              data->m_runSta = UiMotionData::RUN_STA_STOPING;
          }
          data->m_currentCount ++;
          data->m_lock.unlock();
          break;
        case UiMotionData::RUN_STA_STOPING:
        {
          double curVel ;
          m_sev->cmdSetSpdRef(axis,0);
          m_sev->cmdGetSpdFb(axis,curVel);
          data->m_lock.lockForWrite();
          data->m_curTimeout ++;
          if((curVel<data->m_velrangUp)&&(curVel>data->m_velranglow)||(data->m_curTimeout>data->m_timeoutMaxCount))
          {
            m_sev->setAxisServoOn(axis,false);
            data->m_runSta = UiMotionData::RUN_STA_STOP_FINISH;
          }
          data->m_lock.unlock();
          qDebug()<<"axis = "<<axis<<"cur sta = RUN_STA_STOPING "\
                 <<"timerout "<<data->m_curTimeout\
                <<"vel = "<<curVel;
        }
          break;
        case UiMotionData::RUN_STA_STOP_FINISH:
          data->m_lock.lockForWrite();
          data->m_currentCount = 0;
          data->m_curTimeout = 0;
          data->m_start = false;
          data->m_lock.unlock();
//          qDebug()<<"cur sta = RUN_STA_STOP_FINISH ";
          break;
        }

      }
      else
      {

      }
    }

    msleep(MIN_PERIOD);
  }
  qDebug()<<"VmotionThread exit ";
}

