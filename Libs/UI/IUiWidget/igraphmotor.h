#ifndef IGRAPHMOTOR_H
#define IGRAPHMOTOR_H

#include <QWidget>
#include "igraph.h"


class IGraphMotorPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphMotor : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphMotor)
public:
  explicit IGraphMotor(QWidget *parent = 0);
  virtual ~IGraphMotor();

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void visitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;



signals:

public slots:
protected slots:


protected:
  IGraphMotor(IGraphMotorPrivate&dd, QWidget *parent=0);

};

#endif // IGRAPHMOTOR_H
