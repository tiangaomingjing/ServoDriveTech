#ifndef VMOTIONTHREAD_H
#define VMOTIONTHREAD_H

#include <QObject>
#include <QThread>

class UiMotionData;
class SevDevice;

class VmotionThread : public QThread
{
  Q_OBJECT
public:
  explicit VmotionThread(SevDevice *dev,QList<UiMotionData *> dataList,QObject *parent = 0);
  ~VmotionThread();

  void setSevDevice(SevDevice *dev);
  void setUiMotionData(QList<UiMotionData *> data);

  void stop();
  quint16 msdelayTime();

protected:
  void run() Q_DECL_OVERRIDE;

signals:

public slots:

private:
  volatile bool m_bRun;
  QList<UiMotionData *>m_motionDataList;
  SevDevice *m_sev;
};

#endif // VMOTIONTHREAD_H
