#include "curveusrvffd.h"
#include <QVector>
#include <ctkPluginContext.h>
#include <QDebug>

#define VAR_KEYNAME_POS_FFD_SPDR      "gSevDrv.sev_obj.pos.ffd.spdr"
#define CON_KEYNAME_MOT_NOS         "gSevDrv.sev_obj.cur.mot.Nos_1"

CurveUsrVffd::CurveUsrVffd()
{

}

CurveUsrVffd::CurveUsrVffd(ctkPluginContext *context)
{
  qDebug()<<"CurveUsrVffd construct";
  ctkDictionary dic;
  dic.insert("name","CurveUsrVffd");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveUsrVffd::clone()
{
  ICurve *c=new CurveUsrVffd();
  c->prepare();
  return c;
}

void CurveUsrVffd::init()
{
  //设置单位
  //增加变量曲线，常量曲线读取 keyName
  addUnit("rpm",1);
  addUnit("rps",0.0167);
  addUnit("rad/s",0.1047);
  addVarInputByName(VAR_KEYNAME_POS_FFD_SPDR); //对应输入通道 dd.m_varInputs.at(0).datas
  addConstInputByName(CON_KEYNAME_MOT_NOS);//对应输入值 dd.m_constInputs.at(0).constK
}

void CurveUsrVffd::calculate()
{
  double result = 0;
  double nos = dd.m_constInputs.at(0).constK;
//  nos = 5000;
  dd.m_cData.values.clear();
  for(int i = 0;i<dd.m_varInputs.at(0).datas.size();i++)
  {
    result = (dd.m_varInputs.at(0).datas.at(i)/16777216.0)*nos;
    dd.m_cData.values.append(result);
//    qDebug()<<QString("vcmd %1 cal: in = %2,out = %3").arg(dd.m_axisInx).arg(dd.m_varInputs.at(0).datas.at(i)).arg(result);
  }

}

QString CurveUsrVffd::name()
{
  return QString("Vffd");
}

QString CurveUsrVffd::note()
{
  return tr("Pos Velocity Cmd");
}

QString CurveUsrVffd::pluginName()
{
  return "CurveUsrVffd";
}

