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

PlotCurveUsrPos::PlotCurveUsrPos()
{

}

void PlotCurveUsrPos::sayHello()
{
  qDebug()<<"PlotCurveUsrPos HelloWorld";
}

IPlotCurve *PlotCurveUsrPos::clone()
{
  IPlotCurve *c=new PlotCurveUsrPos;
  c->data=this->data;
  return c;
}

