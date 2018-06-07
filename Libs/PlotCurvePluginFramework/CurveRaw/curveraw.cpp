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
  c->reset();
  c->setAxisInx(dd.m_axisInx);
  c->setDevInx(dd.m_devInx);
  c->setName(dd.m_name);
  c->setNote("");
  c->setColor(dd.m_color);
  c->setIsDraw(dd.m_isDraw);
  c->addVarInputByName(dd.m_name);
  c->fillVarInputsPrm(0,dd.m_varInputs.at(0).prm);
  c->setAxisCount(dd.m_axisCount);
  return c;
}

void CurveRaw::init()
{
  setName("gServo.pro.prm.mot");
  addVarInputByName("gServo.pro.prm.mot");
}

void CurveRaw::calculate()
{
  dd.m_cData.values.clear();
  dd.m_cData.values.append(dd.m_varInputs.at(0).datas);
}

void CurveRaw::reset()
{
  dd.m_unitsHash.clear();
  dd.m_unitNameList.clear();
  dd.m_constInputs.clear();
  dd.m_varInputs.clear();
}

QString CurveRaw::displayName()
{
  return dd.m_name.split('.').last();
}

QString CurveRaw::fullName()
{
  return QObject::tr("%1").arg(dd.m_name);
}

QString CurveRaw::pluginName()
{
  return "CurveRaw";
}
