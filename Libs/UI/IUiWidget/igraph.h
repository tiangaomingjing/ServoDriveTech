#ifndef IGRAPH_H
#define IGRAPH_H

#include <QWidget>
#include "iuiwidget_global.h"
class IUiWidget;
class IGraphPrivate;

class IGraph : public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraph)
public:
  explicit IGraph(QWidget *parent = 0);
  virtual ~IGraph();
  virtual void visit(IUiWidget*uiWidget)=0;

signals:

public slots:
protected:
  IGraph(IGraphPrivate&d,QWidget *parent = 0);
  IGraphPrivate *d_ptr;

};

#endif // IGRAPH_H
