#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphposition.h"
#include "igraph_p.h"

class IUIWIDGETSHARED_EXPORT IGraphPositionPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphPosition)
public:
  IGraphPositionPrivate();
  virtual ~IGraphPositionPrivate();
protected:

};

#endif // IGRAPHBRAKE_P_H

