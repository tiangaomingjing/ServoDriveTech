#include "iplotunit.h"
#include "iplotunit_p.h"
#include "uiplot.h"

#include <QDebug>

IPlotUnit::~IPlotUnit()
{

}

void IPlotUnit::visit(IUiWidget *uiWidget)
{
  Q_D(IPlotUnit);
  d->m_uiPlot=dynamic_cast<UiPlot *>(uiWidget);
  qDebug()<<d->m_uiPlot->objectName()<<"ui index axis="<<d->m_uiPlot->uiIndexs().axisInx<<"ui index page="<<d->m_uiPlot->uiIndexs().pageInx;
}

IPlotUnit::IPlotUnit(IPlotUnitPrivate &dd, QWidget *parent):d_ptr(&dd),QWidget(parent)
{
  d_ptr->q_ptr=this;
}

