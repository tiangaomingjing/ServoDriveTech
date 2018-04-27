#include "threadsample.h"
#include <QDebug>
using namespace ComDriver;
ThreadSample::ThreadSample(const QList<DevSamplePrm> &samplPrms, QObject *parent) : QThread(parent),
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
  qDebug()<<"ThreadSample thread id"<<currentThread()->currentThreadId();
  SampleData sample;
  while(m_bRun)
  {
    static quint32 count=0;
    qDebug()<<"ThreadSample run count"<<count;
    sample.curves.clear();

    CurveDatas data;

    sample.devId=0;
    sample.dspId=1;
    for(int i=0;i<100;i++)
      data.push_back(count+i);
    sample.curves.push_back(data);
    emit sampleDataIn(sample);
    count++;
    msleep(80);
  }
  qDebug()<<"exit run";
}

