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
    m_seqPeriod(200),
    m_seqCircleCount(10),
    m_stepAmp(5),
    m_stepTime(5),
    m_start(false),
    m_switch(true),
    m_currentCount(0),
    m_delayStartCount(10),
    m_seqCircleUse(0),
    m_stepIsSetOn(false),
    m_velrangUp(2),
    m_velranglow(-2),
    m_timeoutMaxCount(100),
    m_curTimeout(0)
  {}
  ~UiMotionData(){}
  bool m_isCircle;
  int m_seqAmp;
  quint16 m_seqPeriod;
  quint16 m_seqCircleCount;
  int m_stepAmp;
  quint16 m_stepTime;

  bool m_start;
  bool m_switch;
  quint64 m_currentCount;
  quint32 m_delayStartCount;
  MotionRunSta m_runSta;
  QReadWriteLock m_lock;
  quint16 m_seqCircleUse;
  bool m_stepIsSetOn;

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
