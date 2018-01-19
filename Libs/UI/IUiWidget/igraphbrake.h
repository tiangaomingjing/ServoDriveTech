#ifndef IGRAPHBRAKE_H
#define IGRAPHBRAKE_H

#include <QWidget>
#include "iuiwidget_global.h"
//#include "igraphwidget.h"

class IGraphBrakePrivate;
class IUIWIDGETSHARED_EXPORT IGraphBrake : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphBrake)
public:
  explicit IGraphBrake(QWidget *parent = 0);
  virtual ~IGraphBrake();

signals:

public slots:
protected:
  IGraphBrake(IGraphBrakePrivate&d, QWidget *parent=0);
  IGraphBrakePrivate *d_ptr;
};

#endif // IGRAPHBRAKE_H
