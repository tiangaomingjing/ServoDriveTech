#ifndef UIMOTIONVELOCITY_H
#define UIMOTIONVELOCITY_H

#include <QWidget>
#include <QReadWriteLock>

namespace Ui {
class UiMotionVelocity;
}
class UiMotionData
{

public:
  typedef enum{
    RUN_STA_INIT = 0,
    RUN_STA_CHECK_ON = 1,
    RUN_STA_RUNNING = 2,
    RUN_STA_STOPING = 3,
    RUN_STA_STOP_FINISH = 4
  }MotionRunSta;
  UiMotionData():
    m_isCircle(false),
    m_seqAmp(5),
    m_seqPeriod(500),
    m_seqCircleCount(10),
    m_stepAmp(5),
    m_stepTime(5),
    m_switch(true),
    m_seqCircleUse(0),
    m_velrangUp(10000),
    m_velranglow(-10000),
    m_timeoutMaxCount(1000),
    m_curTimeout(0),
    m_breakByHand(false),
    m_runSta(RUN_STA_STOPING)
  {}
  ~UiMotionData(){}
  bool m_isCircle;
  int m_seqAmp;
  quint16 m_seqPeriod;
  quint16 m_seqCircleCount;
  int m_stepAmp;
  quint16 m_stepTime;

  volatile bool m_breakByHand;
  bool m_switch;

  MotionRunSta m_runSta;
  quint16 m_seqCircleUse;
  quint16 m_stepCircleUse;
  quint16 m_stepCircleCount;

  float m_seqInc;
  float m_stepInc;

  double m_velrangUp;
  double m_velranglow;
  quint16 m_timeoutMaxCount;
  quint16 m_curTimeout;
};

class MotionVelocity;

class UiMotionVelocity : public QWidget
{
  Q_OBJECT

public:
  explicit UiMotionVelocity(MotionVelocity *mv, QWidget *parent = 0);
  ~UiMotionVelocity();
  void updataUi(int axisInx);
  QList<UiMotionData*>uiDataList();

protected:
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private slots:
  void onCheckBoxCircleSWClicked(bool checked);
  void onCssChanged(const QString &css);
  void onSpinBoxValueChanged(int value);

private:
  void setupIcons(const QString &css);

private:
  friend class MotionVelocity;
  Ui::UiMotionVelocity *ui;
  int m_axisCount;
  QList<UiMotionData*>m_uiDataList;
  MotionVelocity *q_ptr;
};

#endif // UIMOTIONVELOCITY_H
