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
  virtual void visit(IUiWidget*ui)Q_DECL_OVERRIDE =0;

signals:

public slots:
protected:
  IGraphStatus(IGraphStatusPrivate&d, QWidget *parent=0);

};

#endif // IGRAPHSTATUS_H
