#ifndef NOLINEARAUTOTURNING_H
#define NOLINEARAUTOTURNING_H

#include <QObject>
#include "sdtglobaldef.h"

class SevDevice;
class QTimer;
class NolinearAutoTurning : public QObject
{
  Q_OBJECT
public:
  explicit NolinearAutoTurning(SevDevice *sev,quint16 axisInx,QObject *parent = 0);
  ~NolinearAutoTurning();

  qreal acc() const;
  void setAcc(qreal acc);

  qreal dec() const;
  void setDec(qreal dec);

  qreal maxSpd() const;
  void setMaxSpd(qreal maxSpd);

  qreal pulseNum() const;
  void setPulseNum(qreal pulseNum);

  bool start();
  void stop();

  quint16 waitMaxCount() const;
  void setWaitMaxCount(quint16 waitMaxCount);

  quint64 autoTnFgd();//103
  quint64 autoTnFgp();//104
  quint64 autoTnFgi();//105
  quint64 autoTnFgn();//106

private:
  void recoverStatus();
  void readAutoTurningResultBeforeServoOff();

signals:
  void progressChanged(int v);
  void autoTurnigFinish(bool ok);
public slots:
  void onTimeOut();
  void onSevDeviceNetError(quint16 axisInx);
private:
  SevDevice *m_sev;
  quint16 m_axisInx;
  qreal m_acc;
  qreal m_dec;
  qreal m_maxSpd;
  qreal m_pulseNum;
  QTimer *m_timer;
  quint32 m_waitCount;
  quint32 m_waitMaxCount;
  qint8 m_progressValue;
  GT::ModeCtlType m_prevMode;
  GT::SevControlSrc m_prevSrc;

  quint64 m_retFgd;
  quint64 m_retFgp;
  quint64 m_retFgi;
  quint64 m_retFgn;

};

#endif // NOLINEARAUTOTurning_H
