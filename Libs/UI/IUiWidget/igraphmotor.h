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
  virtual void visit(IUiWidget*ui)Q_DECL_OVERRIDE=0;

signals:

public slots:
protected:
  IGraphMotor(IGraphMotorPrivate&d, QWidget *parent=0);

};

#endif // IGRAPHMOTOR_H
