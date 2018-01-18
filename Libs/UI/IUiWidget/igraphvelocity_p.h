#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphvelocity.h"
class IGraphVelocityPrivate
{
  Q_DECLARE_PUBLIC(IGraphVelocity)
public:
  IGraphVelocityPrivate(){}
  virtual ~IGraphVelocityPrivate(){}
protected:
  IGraphVelocity *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

