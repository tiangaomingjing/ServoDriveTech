#ifndef IGRAPHMOTOR_H
#define IGRAPHMOTOR_H

#include <QWidget>
#include "iuiwidget_global.h"
//#include "igraphwidget.h"

class IGraphMotorPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphMotor : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphMotor)
public:
  explicit IGraphMotor(QWidget *parent = 0);
  virtual ~IGraphMotor();
  virtual void accept(IUiWidget*ui)=0;

signals:

public slots:
protected:
  IGraphMotor(IGraphMotorPrivate&d, QWidget *parent=0);
  IGraphMotorPrivate *d_ptr;
};

#endif // IGRAPHMOTOR_H
