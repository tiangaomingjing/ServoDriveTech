#ifndef THREADCALCULATE_H
#define THREADCALCULATE_H

#include <QObject>
#include <QThread>
#include "sampledata.h"

class CalculateWorker : public QObject
{
  Q_OBJECT
public:
  explicit CalculateWorker(QObject *parent = 0);
  ~CalculateWorker();

public slots:
  void onSampleDataIn(SampleData data);
private:

};

class ThreadCalculate : public QThread
{
  Q_OBJECT
public:
  explicit ThreadCalculate(QObject *parent = 0);
  ~ThreadCalculate();

protected:
  void run() Q_DECL_OVERRIDE;

signals:
  void sampleDataIn(SampleData data);

public slots:

};

#endif // THREADCALCULATE_H
