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

PlotCurveRaw::PlotCurveRaw()
{

}

void PlotCurveRaw::sayHello()
{
  qDebug()<<"plotCurveRaw HelloWorld";
}

IPlotCurve *PlotCurveRaw::clone()
{
  IPlotCurve *c=new PlotCurveRaw;
  c->data=this->data;
  return c;
}

