﻿#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphbrake.h"
#include "igraph_p.h"
#include "iuiwidget_global.h"

class IUIWIDGETSHARED_EXPORT IGraphBrakePrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphBrake)
public:
  IGraphBrakePrivate(){}
  virtual ~IGraphBrakePrivate(){}
protected:

};

#endif // IGRAPHBRAKE_P_H

