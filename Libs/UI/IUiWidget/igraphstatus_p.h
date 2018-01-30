#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphstatus.h"
#include "igraph_p.h"

class IUIWIDGETSHARED_EXPORT IGraphStatusPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphStatus)
public:
  IGraphStatusPrivate();
  virtual ~IGraphStatusPrivate();
protected:

};

#endif // IGRAPHBRAKE_P_H

