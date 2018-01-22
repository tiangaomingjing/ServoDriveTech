#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphmotor.h"
class SevDevice;
class QTreeWidget;
class IGraphMotorPrivate
{
  Q_DECLARE_PUBLIC(IGraphMotor)
public:
  IGraphMotorPrivate(){}
  virtual ~IGraphMotorPrivate(){}
protected:
  IGraphMotor *q_ptr;
  SevDevice *m_dev;
  QTreeWidget *m_treeWidget;
};

#endif // IGRAPHBRAKE_P_H

