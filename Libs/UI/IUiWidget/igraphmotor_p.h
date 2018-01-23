#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphmotor.h"
#include "iuiwidget_global.h"
class SevDevice;
class QTreeWidget;
class BoxItemMapping;
class IUIWIDGETSHARED_EXPORT IGraphMotorPrivate
{
  Q_DECLARE_PUBLIC(IGraphMotor)
public:
  IGraphMotorPrivate();
  virtual ~IGraphMotorPrivate();

protected:
  IGraphMotor *q_ptr;
  SevDevice *m_dev;
  QTreeWidget *m_treeWidget;
  BoxItemMapping*m_mapping;
};

#endif // IGRAPHBRAKE_P_H

