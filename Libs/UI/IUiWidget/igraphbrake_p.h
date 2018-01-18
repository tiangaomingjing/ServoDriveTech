#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphbrake.h"
class IGraphBrakePrivate
{
  Q_DECLARE_PUBLIC(IGraphBrake)
public:
  IGraphBrakePrivate(){}
  virtual ~IGraphBrakePrivate(){}
protected:
  IGraphBrake *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

