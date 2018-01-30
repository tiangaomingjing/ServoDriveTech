#ifndef IGRAPHSTATUS_H
#define IGRAPHSTATUS_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"

class IGraphStatusPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphStatus : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphStatus)
public:
  explicit IGraphStatus(QWidget *parent = 0);
  virtual ~IGraphStatus();

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void visitActive(IUiWidget*uiWidget)Q_DECL_OVERRIDE =0;

signals:

public slots:
protected:
  IGraphStatus(IGraphStatusPrivate&dd, QWidget *parent=0);

};

#endif // IGRAPHSTATUS_H
