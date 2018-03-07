#ifndef IGRAPHVELOCITY_H
#define IGRAPHVELOCITY_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"
#include "igraph.h"

class IGraphVelocityPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphVelocity : public IGraphWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphVelocity)
public:
  explicit IGraphVelocity(QWidget *parent = 0);
  virtual ~IGraphVelocity();

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void setCustomVisitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;

signals:

public slots:
protected:
  IGraphVelocity(IGraphVelocityPrivate&dd, QWidget *parent=0);

};

#endif // IGRAPHVELOCITY_H
