#include "threadcalculate.h"
#include <QDebug>
using namespace ComDriver;
CalculateWorker::CalculateWorker(const QList<DevCurves> & devCurves,QObject *parent) : QObject(parent),
  m_devCurves(devCurves)
{

}

CalculateWorker::~CalculateWorker()
{

}
int CalculateWorker::maxPointSize()
{
  return 1000;
}

void CalculateWorker::onSampleDataIn(SampleData data)
{
//  qDebug()<<"CalculateWorker handle data"<<count;
//  qDebug()<<"dev inx = "<<data.devId<<"dsp inx = "<<data.dspId;
  CurveListIterator it=data.curves.begin();

  const DevCurves *devCurve=NULL;
  for(int i=0;i<m_devCurves.size();i++)
  {
    if(m_devCurves.at(i).m_devInx==data.devId)
    {
      devCurve=&(m_devCurves.at(i));
      break;
    }
  }
  const DSPCurves *dspCurves=NULL;
  for(int i=0;i<devCurve->m_dspCurves.size();i++)
  {
    if(devCurve->m_dspCurves.at(i).m_dspInx==data.dspId)
    {
      dspCurves = &(devCurve->m_dspCurves.at(i));
    }
  }


  int cInx=0;
  ICurve *c;
  PlotData pd;
  for(;it!=data.curves.end();)
  {
    c=dspCurves->m_curves.at(cInx);
    //曲线输入，并计算
    for(int i=0;i<c->varInputsKeys().size();i++)
    {
      CurveDatas vec= *it;
      c->setVarInputVector(i,QVector<double>::fromStdVector(vec));
      it++;
    }
    c->exec();

    //取样输出
    CurveData cData;
//    int maxPoint=maxPointSize();
//    quint16 size=c->cData()->values.size();
//    int interval=size/maxPoint;
//    if(interval == 0)
//      interval = 1;
////    qDebug()<<"interval = "<<interval<<" size = "<<size;
//    for(int i=0;i<size;i++)
//    {
//      if(0 == i%interval)
//      {
//        cData.keys.append(c->cData()->keys.at(i));
//        cData.values.append(c->cData()->values.at(i));
//      }
//    }

    cData.keys.append(c->cData()->keys);
    cData.values.append(c->cData()->values);

    pd.m_dataHash.insert(c,cData);
    cInx++;
  }
  emit plotDataIn(pd);
}

ThreadCalculate::ThreadCalculate(const QList<DevCurves> devCurves,QObject *parent) : QThread(parent),
  m_devCurves(devCurves)
{
  qRegisterMetaType<PlotData>("PlotData");//信号与槽发送自己定义的数据
}

ThreadCalculate::~ThreadCalculate()
{
  qDebug()<<"~ThreadCalculate begin";
  quit();
  wait();
  qDebug()<<"~ThreadCalculate end";
}


void ThreadCalculate::run()
{
  qDebug()<<"ThreadCalculate thread id"<<currentThreadId();
  CalculateWorker worker(m_devCurves);
  connect(&worker,SIGNAL(plotDataIn(PlotData)),this,SIGNAL(plotDataIn(PlotData)),Qt::QueuedConnection);
  connect(this,SIGNAL(sampleDataIn(SampleData)),&worker,SLOT(onSampleDataIn(SampleData)),Qt::QueuedConnection);
  exec();
}



