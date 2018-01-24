#ifndef IGRAPH_H
#define IGRAPH_H

#include <QWidget>
#include "iuiwidget_global.h"
class IUiWidget;
class IGraphPrivate;

class IUIWIDGETSHARED_EXPORT IGraph:public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraph)
public:
  explicit IGraph(QWidget *parent=0);
  virtual ~IGraph();
  virtual void visit(IUiWidget*uiWidget);

protected:
  virtual void setUiVersionName()=0;
  virtual void visitActive(IUiWidget*uiWidget)=0;

signals:

public slots:
protected:
  IGraph(IGraphPrivate&dd,QWidget *parent=0);
  IGraphPrivate *d_ptr;

};

#endif // IGRAPH_H
