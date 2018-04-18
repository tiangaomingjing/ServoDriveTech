#include "plotcurveusrpos.h"
#include "iplotcurve.h"
#include <ctkPluginContext.h>

#include <QDebug>

PlotCurveUsrPos::PlotCurveUsrPos(ctkPluginContext *context)
{
  ctkDictionary dic;
  dic.insert("name","PlotCurveUsrPos");
  context->registerService<IPlotCurve>(this,dic);
}

void PlotCurveUsrPos::sayHello()
{
  qDebug()<<"PlotCurveUsrPos HelloWorld";
}

