#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphmotor.h"
class IGraphMotorPrivate
{
  Q_DECLARE_PUBLIC(IGraphMotor)
public:
  IGraphMotorPrivate(){}
  virtual ~IGraphMotorPrivate(){}
protected:
  IGraphMotor *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

