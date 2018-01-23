#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphcurrent.h"
class IGraphCurrentPrivate
{
  Q_DECLARE_PUBLIC(IGraphCurrent)
public:
  IGraphCurrentPrivate(){}
  virtual ~IGraphCurrentPrivate(){}
protected:
  IGraphCurrent *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

