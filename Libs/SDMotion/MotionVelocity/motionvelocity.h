#ifndef MOTIONVELOCITY_H
#define MOTIONVELOCITY_H

#include "motionvelocity_global.h"
#include "imotion.h"

class MotionVelocityPrivate;
class UiMotionVelocity;

class MOTIONVELOCITYSHARED_EXPORT MotionVelocity :public IMotion
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(MotionVelocity)

public:
  explicit MotionVelocity(QListWidget *axisListWidget,SevDevice *sev ,const QString &name = "velocity",QObject *parent = 0);
  ~MotionVelocity();

  void movePrepare(quint16 axisInx) Q_DECL_OVERRIDE;
  bool move(quint16 axisInx) Q_DECL_OVERRIDE;
  bool stop(quint16 axisInx) Q_DECL_OVERRIDE;
  void updateAxisUi(quint16 axisInx) Q_DECL_OVERRIDE;
  void setMode() Q_DECL_OVERRIDE;

private slots:
  void onMotionFinish(quint16 axisInx);

private:
  UiMotionVelocity * UiMotion();
};

#endif // MOTIONVELOCITY_H
