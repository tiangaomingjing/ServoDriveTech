#include "plotcurverawactivator.h"
#include "iplotcurve.h"
#include "plotcurveraw.h"

#include <QDebug>

PlotCurveRawActivator::PlotCurveRawActivator() :
  m_iPlotCurve(NULL)
{

}

void PlotCurveRawActivator::start(ctkPluginContext *context)
{
  qDebug()<<"new plotcurve raw";
  m_iPlotCurve=new PlotCurveRaw(context);

}

void PlotCurveRawActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iPlotCurve!=NULL)
  {
    delete m_iPlotCurve;
    m_iPlotCurve=NULL;
  }
  qDebug()<<"PlotCurveRaw stop";
}

