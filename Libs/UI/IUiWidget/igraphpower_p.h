#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphpower.h"
class IGraphPowerPrivate
{
  Q_DECLARE_PUBLIC(IGraphPower)
public:
  IGraphPowerPrivate(){}
  virtual ~IGraphPowerPrivate(){}
protected:
  IGraphPower *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

