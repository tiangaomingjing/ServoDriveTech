#include "curveusrpos.h"
#include <QVector>
#include <ctkPluginContext.h>
#include <QDebug>

#define VAR_KEYNAME_POS "gSevDrv.sev_obj.cur.rsv.pos"

CurveUsrPos::CurveUsrPos()
{

}

CurveUsrPos::CurveUsrPos(ctkPluginContext *context)
{
  qDebug()<<"CurveUsrPos construct";
  ctkDictionary dic;
  dic.insert("name","CurveUsrPos");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveUsrPos::clone()
{
  ICurve *c=new CurveUsrPos();
  c->prepare();
  return c;
}

void CurveUsrPos::init()
{
  //设置单位
  //增加变量曲线，常量曲线读取 keyName
  addUnit("pulse",1);
  addVarInputByName(VAR_KEYNAME_POS);

}

void CurveUsrPos::calculate()
{
  dd.m_cData.values.clear();
  dd.m_cData.values.append(dd.m_varInputs.at(0).datas);
}

QString CurveUsrPos::name()
{
  return QString("Pos");
}

QString CurveUsrPos::note()
{
  return tr("PositionFeedback");
}

