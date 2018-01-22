#ifndef IGRAPHCURRENT_H
#define IGRAPHCURRENT_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"
class IGraphCurrentPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphCurrent : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphCurrent)
public:
  explicit IGraphCurrent(QWidget *parent = 0);
  virtual ~IGraphCurrent();
  virtual void accept(IUiWidget*ui)=0;

signals:

public slots:
protected:
  IGraphCurrent(IGraphCurrentPrivate&d, QWidget *parent=0);
  IGraphCurrentPrivate *d_ptr;
};

#endif // IGRAPHCURRENT_H
