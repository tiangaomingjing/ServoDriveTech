#include "curveraw.h"
#include <QVector>
#include <ctkPluginContext.h>

#include <QDebug>

CurveRaw::CurveRaw()
{

}

CurveRaw::CurveRaw(ctkPluginContext *context)
{
  qDebug()<<"CurveRaw construct";
  ctkDictionary dic;
  dic.insert("name","CurveRaw");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveRaw::clone()
{
  ICurve *c=new CurveRaw();
  c->prepare();
  return c;
}

void CurveRaw::calculate()
{
  dd.m_cData.values.clear();
  dd.m_cData.values.append(dd.m_varInputs.at(0).datas);
}

QString CurveRaw::displayName()
{
  return dd.m_name.split('.').last();
}

QString CurveRaw::fullName()
{
  return QObject::tr("%1").arg(dd.m_name);
}
