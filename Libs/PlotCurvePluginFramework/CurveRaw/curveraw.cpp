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
  return c;
}

void CurveRaw::calculate()
{
  m_cData.values=m_varInputs.at(0).datas;

}

QString CurveRaw::displayName()
{
  return m_name.split('.').last();
}

QString CurveRaw::fullName()
{
  return QObject::tr("%1").arg(m_name);
}
