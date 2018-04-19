#include "curveraw.h"
#include <QVector>
#include <ctkPluginContext.h>

CurveRaw::CurveRaw()
{

}

CurveRaw::CurveRaw(ctkPluginContext *context)
{
  ctkDictionary dic;
  dic.insert("name","CurveRaw");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveRaw::clone()
{
  ICurve *c=new CurveRaw();
  return c;
}

void CurveRaw::calculate()
{
  m_cData.values=m_varInputs.at(0).datas;

}
