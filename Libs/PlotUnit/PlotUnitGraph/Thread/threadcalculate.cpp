#include "threadcalculate.h"
#include <QDebug>
using namespace ComDriver;
CalculateWorker::CalculateWorker(QObject *parent) : QObject(parent)
{

}

CalculateWorker::~CalculateWorker()
{

}

void CalculateWorker::onSampleDataIn(SampleData data)
{
  static int count = 0;
  qDebug()<<"CalculateWorker handle data"<<count;
  qDebug()<<"devId "<<data.devId<<"dspId"<<data.dspId;
  count ++ ;
  CurveListIterator it=data.curves.begin();


  for(;it!=data.curves.end();it++)
  {
    CurveDatas vec= *it;
    QVector<double> v=QVector<double>::fromStdVector(vec);
    qDebug()<<"vector size "<<vec.size()<<"  QVector size"<<v.size();
//    CurveDatasIterator dIt = vec.begin();
//    double v;
//    for(;dIt!=vec.end();dIt++)
//    {
//      v=*dIt;
//      qDebug()<<v;
//    }
  }
}

ThreadCalculate::ThreadCalculate(QObject *parent) : QThread(parent)
{

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
  CalculateWorker worker;
  connect(this,SIGNAL(sampleDataIn(SampleData)),&worker,SLOT(onSampleDataIn(SampleData)),Qt::QueuedConnection);
  exec();
}



