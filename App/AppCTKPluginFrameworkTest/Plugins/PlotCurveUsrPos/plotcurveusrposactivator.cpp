#include "plotcurveusrposactivator.h"
#include "iplotcurve.h"
#include "plotcurveusrpos.h"

#include <QDebug>

PlotCurveUsrPosActivator::PlotCurveUsrPosActivator() :
  m_iPlotCurve(NULL)
{

}

void PlotCurveUsrPosActivator::start(ctkPluginContext *context)
{
  qDebug()<<"new plotcurve usr pos";
  m_iPlotCurve=new PlotCurveUsrPos(context);
}

void PlotCurveUsrPosActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iPlotCurve!=NULL)
  {
    delete m_iPlotCurve;
    m_iPlotCurve=NULL;
  }
  qDebug()<<"PlotCurveUsrPos stop";
}

