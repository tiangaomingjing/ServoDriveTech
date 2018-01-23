#ifndef IGRAPHPOSITION_H
#define IGRAPHPOSITION_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraphwidget.h"
#include "igraph.h"

class IGraphPositionPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphPosition : public IGraphWidget,public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphPosition)
public:
  explicit IGraphPosition(QWidget *parent = 0);
  virtual ~IGraphPosition();
  virtual void visit(IUiWidget*ui)Q_DECL_OVERRIDE=0;
signals:

public slots:
protected:
  IGraphPosition(IGraphPositionPrivate&d, QWidget *parent=0);
};

#endif // IGRAPHPOSITION_H
