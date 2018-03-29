#include "iplotunitgraph.h"
#include "uiplot.h"
#include "iuiwidget.h"
#include "iplotunitgraph_p.h"

#include <QDebug>

IPlotUnitGraph::~IPlotUnitGraph()
{

}

void IPlotUnitGraph::visit(IUiWidget *uiWidget)
{
  Q_D(IPlotUnitGraph);
  d->m_uiPlot=dynamic_cast<UiPlot *>(uiWidget);
  qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~IPlotUnitGraph visit"<<d->m_uiPlot->objectName();
}

IPlotUnitGraph::IPlotUnitGraph(IPlotUnitGraphPrivate &dd, QWidget *parent):IPlotUnit(dd,parent)
{

}

