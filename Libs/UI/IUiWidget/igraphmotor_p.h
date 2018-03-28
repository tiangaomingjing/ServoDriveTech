#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphmotor.h"
#include "igraph_p.h"
#include "iuiwidget_global.h"

class IUIWIDGETSHARED_EXPORT IGraphMotorPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphMotor)
public:
  IGraphMotorPrivate(){}
  virtual ~IGraphMotorPrivate(){}

protected:

};

#endif // IGRAPHBRAKE_P_H

