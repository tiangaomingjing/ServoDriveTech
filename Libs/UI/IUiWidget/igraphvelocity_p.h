#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphvelocity.h"
#include "igraph_p.h"
class IUIWIDGETSHARED_EXPORT IGraphVelocityPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphVelocity)
public:
  IGraphVelocityPrivate();
  virtual ~IGraphVelocityPrivate();
protected:

};

#endif // IGRAPHBRAKE_P_H

