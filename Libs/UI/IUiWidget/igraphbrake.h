#ifndef IGRAPHBRAKE_H
#define IGRAPHBRAKE_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"

class IGraphBrakePrivate;
class IUiWidget;

class IUIWIDGETSHARED_EXPORT IGraphBrake : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphBrake)
public:
  virtual ~IGraphBrake();
protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void setCustomVisitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;
  virtual void setupDataMappings()=0;

signals:

public slots:
protected:
  IGraphBrake(IGraphBrakePrivate&dd, QWidget *parent=0);
};

#endif // IGRAPHBRAKE_H
