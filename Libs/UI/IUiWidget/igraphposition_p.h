#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphposition.h"
class IGraphPositionPrivate
{
  Q_DECLARE_PUBLIC(IGraphPosition)
public:
  IGraphPositionPrivate(){}
  virtual ~IGraphPositionPrivate(){}
protected:
  IGraphPosition *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

