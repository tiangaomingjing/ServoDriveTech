#ifndef IGRAPHPOWER_H
#define IGRAPHPOWER_H

#include <QWidget>
#include "iuiwidget_global.h"
//#include "igraphwidget.h"

class IGraphPowerPrivate;
class IUIWIDGETSHARED_EXPORT IGraphPower : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphPower)
public:
  explicit IGraphPower(QWidget *parent = 0);

signals:

public slots:
protected:
  IGraphPower(IGraphPowerPrivate&d, QWidget *parent=0);
  IGraphPowerPrivate *d_ptr;
};

#endif // IGRAPHPOWER_H
