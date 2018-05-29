#include "curveusrperr.h"
#include <QVector>
#include <ctkPluginContext.h>
#include <QDebug>

#define VAR_KEYNAME_PERR "gSevDrv.sev_obj.pos.ctl.err"

CurveUsrPerr::CurveUsrPerr()
{

}

CurveUsrPerr::CurveUsrPerr(ctkPluginContext *context)
{
  qDebug()<<"CurveUsrPerr construct";
  ctkDictionary dic;
  dic.insert("name","CurveUsrPerr");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveUsrPerr::clone()
{
  ICurve *c=new CurveUsrPerr();
  c->prepare();
//  c->setPluginName(dd.m_pluginName);
  return c;
}

void CurveUsrPerr::init()
{
  //设置单位
  //增加变量曲线，常量曲线读取 keyName
  addUnit("pulse",1);
  addVarInputByName(VAR_KEYNAME_PERR);

}

void CurveUsrPerr::calculate()
{
  dd.m_cData.values.clear();
  dd.m_cData.values.append(dd.m_varInputs.at(0).datas);
}

QString CurveUsrPerr::name()
{
  return QString("Perr");
}

QString CurveUsrPerr::note()
{
  return tr("PositionError");
}

QString CurveUsrPerr::pluginName()
{
  return "CurveUsrPerr";
}

