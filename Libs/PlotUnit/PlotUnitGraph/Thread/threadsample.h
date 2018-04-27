#ifndef THREADSAMPLE_H
#define THREADSAMPLE_H

#include <QObject>
#include <QThread>

#include "sampledata.h"
#include "curvemanager.h"

class ThreadSample : public QThread
{
  Q_OBJECT
public:
  explicit ThreadSample(const QList<DevSamplePrm> &samplPrms,QObject *parent = 0);
  ~ThreadSample();

  void stop();

protected:
  void run() Q_DECL_OVERRIDE;

signals:
  void sampleDataIn(SampleData data);

public slots:
private:
  volatile bool m_bRun;
  QList<DevSamplePrm> m_samplPrms;
};

#endif // THREADSAMPLE_H
