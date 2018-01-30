#ifndef IGRAPHPOWER_H
#define IGRAPHPOWER_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"

class IGraphPowerPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphPower : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphPower)
public:
  explicit IGraphPower(QWidget *parent = 0);
  virtual ~IGraphPower();

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void visitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;

signals:

public slots:
protected:
  IGraphPower(IGraphPowerPrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHPOWER_H
