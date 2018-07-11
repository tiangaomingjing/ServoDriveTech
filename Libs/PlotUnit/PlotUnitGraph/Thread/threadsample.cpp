#include "threadsample.h"
#include "sevdevice.h"
#include <QDebug>

using namespace ComDriver;
ThreadSample::ThreadSample(const QList<SevDevice *> &sevList,const QList<DevSamplePrm> &samplPrms, QObject *parent) : QThread(parent),
  m_sevList(sevList),
  m_samplPrms(samplPrms)
{
  qRegisterMetaType<SampleData>("SampleData");//信号与槽发送自己定义的数据
  qDebug()<<"init thread id"<<currentThreadId();
}

ThreadSample::~ThreadSample()
{
  qDebug()<<"~ThreadSample begin";
  stop();
  quit();
  wait();
  qDebug()<<"~ThreadSample end";
}

void ThreadSample::stop()
{
  m_bRun = false;
}

void ThreadSample::run()
{
  bool ret =true;
  qDebug()<<"ThreadSample thread id"<<currentThread()->currentThreadId();

  //关闭画图
  stopSampling();
  //打开画图
  ret=startSampling();
  if(ret == false)
  {
    qDebug()<<"startSampling error ";
    return;
  }

  SampleData sample;
  const DevSamplePrm *samplPrmPtr;
  const PlotControlPrm *prm;
  while(m_bRun)
  {
    static quint32 count=0;
//    qDebug()<<"ThreadSample run count"<<count;
    sample.curves.clear();


    for(int i=0;i<m_samplPrms.size();i++)//设备
    {
      samplPrmPtr=&(m_samplPrms.at(i));
      sample.devId=samplPrmPtr->m_devInx;
      for(int j=0;j<samplPrmPtr->m_prms.size();j++)//DSP
      {
//        CurveDatas data;
        prm=&(samplPrmPtr->m_prms.at(j));//DSP j
        sample.dspId=prm->dspIndex;
        m_sevList.at(sample.devId)->getPlotData(*prm,sample.curves);
        if(sample.curves.size() > 0)
          emit sampleDataIn(sample);
      }
    }

    count++;
    msleep(60);
  }

  stopSampling();
  qDebug()<<"exit run";
}

void ThreadSample::stopSampling()
{
  const DevSamplePrm *samplPrmPtr;
  for(int i=0;i<m_samplPrms.size();i++)
  {
     samplPrmPtr=&(m_samplPrms.at(i));
     const PlotControlPrm *prm;
     for(int j=0;j<samplPrmPtr->m_prms.size();j++)
     {
       prm=&(samplPrmPtr->m_prms.at(j));
       m_sevList.at(samplPrmPtr->m_devInx)->stopPlot(*prm);
       qDebug()<<"stop sampling dsp =  "<<prm->dspIndex;
     }
  }
}

bool ThreadSample::startSampling()
{
  bool ret=true;
  DevSamplePrm *samplPrmPtr;
  for(int i=0;i<m_samplPrms.size();i++)
  {
     samplPrmPtr=&(m_samplPrms[i]);
     PlotControlPrm *prm;
     for(int j=0;j<samplPrmPtr->m_prms.size();j++)
     {
       prm=&(samplPrmPtr->m_prms[j]);
       prm->enable=ComDriver::PLOT_ENABLE;
       ret=m_sevList.at(samplPrmPtr->m_devInx)->startPlot(*prm);
       if(ret==false)
         return ret;
       qDebug()<<"start sampling dsp =  "<<prm->dspIndex;
     }
  }
  return ret;
}

