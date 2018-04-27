#ifndef THREADSAMPLE_H
#define THREADSAMPLE_H

#include <QObject>
#include <QThread>

#include "sampledata.h"
#include "curvemanager.h"

class SevDevice;

class ThreadSample : public QThread
{
  Q_OBJECT
public:
  explicit ThreadSample(const QList<SevDevice *> &sevList,const QList<DevSamplePrm> &samplPrms,QObject *parent = 0);
  ~ThreadSample();

  void stop();

protected:
  void run() Q_DECL_OVERRIDE;

signals:
  void sampleDataIn(SampleData data);

public slots:
private:
  void stopSampling();
  bool startSampling();
private:
  volatile bool m_bRun;
  QList<DevSamplePrm> m_samplPrms;
  QList<SevDevice *> m_sevList;
};

#endif // THREADSAMPLE_H
