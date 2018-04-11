#ifndef IPLOTUNITGRAPH_H
#define IPLOTUNITGRAPH_H

#include <QWidget>
#include "iplotunit.h"
#include "plotunitgraph_global.h"
class IPlotUnitGraphPrivate;

class PLOTUNITGRAPHSHARED_EXPORT IPlotUnitGraph : public IPlotUnit
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IPlotUnitGraph)

public:
  virtual ~IPlotUnitGraph();
  virtual void visit(IUiWidget *uiWidget) Q_DECL_OVERRIDE;

signals:

public slots:


protected:
  IPlotUnitGraph(IPlotUnitGraphPrivate&dd,QWidget *parent=0);
};

#endif // IPLOTUNITGRAPH_H
