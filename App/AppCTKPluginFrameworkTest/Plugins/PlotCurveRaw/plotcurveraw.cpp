#include "plotcurveraw.h"
#include "iplotcurve.h"
#include <ctkPluginContext.h>

#include <QDebug>

PlotCurveRaw::PlotCurveRaw(ctkPluginContext *context)
{
  ctkDictionary dic;
  dic.insert("name","PlotCurveRaw");
  context->registerService<IPlotCurve>(this,dic);
}

void PlotCurveRaw::sayHello()
{
  qDebug()<<"plotCurveRaw HelloWorld";
}

