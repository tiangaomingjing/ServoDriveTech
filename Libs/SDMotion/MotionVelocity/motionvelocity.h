#ifndef MOTIONVELOCITY_H
#define MOTIONVELOCITY_H

#include "motionvelocity_global.h"
#include "imotion.h"

class MotionVelocityPrivate;

class MOTIONVELOCITYSHARED_EXPORT MotionVelocity :public IMotion
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(MotionVelocity)
public:
  explicit MotionVelocity(SevDevice *sev ,const QString &name = "velocity",QObject *parent = 0);
  ~MotionVelocity();

  bool move(quint16 axisInx) Q_DECL_OVERRIDE;
  bool stop(quint16 axisInx) Q_DECL_OVERRIDE;
  void updateAxisUi(quint16 axisInx) Q_DECL_OVERRIDE;
};

#endif // MOTIONVELOCITY_H
