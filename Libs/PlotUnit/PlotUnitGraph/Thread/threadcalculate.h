#ifndef THREADCALCULATE_H
#define THREADCALCULATE_H

#include <QObject>
#include <QThread>
#include "sampledata.h"
#include "curvemanager.h"
#include "icurve.h"
#include "plotdata.h"


class CalculateWorker : public QObject
{
  Q_OBJECT
public:
  explicit CalculateWorker(const QList<DevCurves> & devCurves,QObject *parent = 0);
  ~CalculateWorker();

public slots:
  void onSampleDataIn(SampleData data);
signals:
  void plotDataIn(PlotData data);
private:
  int maxPointSize();
private:
  QList<DevCurves> m_devCurves;
  int m_maxPoint;

};

class ThreadCalculate : public QThread
{
  Q_OBJECT
public:
  explicit ThreadCalculate(const QList<DevCurves> devCurves,QObject *parent = 0);
  ~ThreadCalculate();

protected:
  void run() Q_DECL_OVERRIDE;

signals:
  void sampleDataIn(SampleData data);
  void plotDataIn(PlotData data);

public slots:
private:

private:
  QList<DevCurves> m_devCurves;
};

#endif // THREADCALCULATE_H
