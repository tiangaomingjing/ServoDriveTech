#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphstatus.h"
class IGraphStatusPrivate
{
  Q_DECLARE_PUBLIC(IGraphStatus)
public:
  IGraphStatusPrivate(){}
  virtual ~IGraphStatusPrivate(){}
protected:
  IGraphStatus *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

