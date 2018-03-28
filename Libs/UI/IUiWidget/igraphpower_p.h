#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraph_p.h"
#include "igraphpower.h"
#include "iuiwidget_global.h"

class IUIWIDGETSHARED_EXPORT IGraphPowerPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphPower)
public:
  IGraphPowerPrivate(){}
  virtual ~IGraphPowerPrivate(){}
protected:

};

#endif // IGRAPHBRAKE_P_H

