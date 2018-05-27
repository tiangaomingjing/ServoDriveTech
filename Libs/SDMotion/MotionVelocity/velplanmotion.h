#ifndef VELPLANMOTION_H
#define VELPLANMOTION_H

#include <QObject>
#include <QTimer>
class SevDevice;
class UiMotionData;

class VelPlanMotion : public QObject
{
  Q_OBJECT
public:
  explicit VelPlanMotion(quint16 axisInx,SevDevice *dev,UiMotionData * data,QObject *parent = 0);
  ~VelPlanMotion();
  QTimer *timer();
  void movePrepare();
  void move();
  void stop();

signals:
  void motionFinish(quint16 axisInx);
  void progressValueChanged(quint16 axisInx,int value);

public slots:
private slots:
  void onTimerOut();
private:
  QTimer m_timer;
  SevDevice *m_sev;
  UiMotionData *m_data;
  quint16 m_axisInx;
};

#endif // VELPLANMOTION_H
