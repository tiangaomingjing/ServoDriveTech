#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphencoder.h"
class IGraphEncoderPrivate
{
  Q_DECLARE_PUBLIC(IGraphEncoder)
public:
  IGraphEncoderPrivate(){}
  virtual ~IGraphEncoderPrivate(){}
protected:
  IGraphEncoder *q_ptr;
};

#endif // IGRAPHBRAKE_P_H

