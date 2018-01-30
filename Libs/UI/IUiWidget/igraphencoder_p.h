#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphencoder.h"
#include "igraph_p.h"

class IUIWIDGETSHARED_EXPORT IGraphEncoderPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphEncoder)
public:
  IGraphEncoderPrivate();
  virtual ~IGraphEncoderPrivate();
protected:

};

#endif // IGRAPHBRAKE_P_H

