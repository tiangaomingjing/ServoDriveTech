#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphcurrent.h"
#include "igraph_p.h"

class IUIWIDGETSHARED_EXPORT IGraphCurrentPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphCurrent)
public:
  IGraphCurrentPrivate();
  virtual ~IGraphCurrentPrivate();
protected:

};

#endif // IGRAPHBRAKE_P_H

