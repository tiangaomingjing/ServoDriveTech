#ifndef IGRAPHPOSITION_H
#define IGRAPHPOSITION_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"

class IGraphPositionPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphPosition : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphPosition)
public:
  explicit IGraphPosition(QWidget *parent = 0);
  virtual ~IGraphPosition();
  virtual void accept(IUiWidget*ui)=0;
signals:

public slots:
protected:
  IGraphPosition(IGraphPositionPrivate&d, QWidget *parent=0);
  IGraphPositionPrivate *d_ptr;
};

#endif // IGRAPHPOSITION_H
