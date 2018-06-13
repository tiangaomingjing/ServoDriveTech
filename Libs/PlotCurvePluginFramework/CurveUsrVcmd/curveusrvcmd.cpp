#include "curveusrvcmd.h"
#include <QVector>
#include <ctkPluginContext.h>
#include <QDebug>

#define VAR_KEYNAME_CTL_SPD_REF   "gSevDrv.sev_obj.vel.ctl.spd_ref"
#define CON_KEYNAME_MOT_NOS        "gSevDrv.sev_obj.cur.mot.Nos_1"

CurveUsrVcmd::CurveUsrVcmd()
{

}

CurveUsrVcmd::CurveUsrVcmd(ctkPluginContext *context)
{
  qDebug()<<"CurveUsrVcmd construct";
  ctkDictionary dic;
  dic.insert("name","CurveUsrVcmd");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveUsrVcmd::clone()
{
  ICurve *c=new CurveUsrVcmd();
  c->prepare();
  c->setUnit(dd.m_unitName);
  c->setAxisInx(dd.m_axisInx);
  c->setAxisCount(dd.m_axisCount);
  c->setDevInx(dd.m_devInx);
  c->setColor(dd.m_color);
  c->setIsDraw(dd.m_isDraw);

  for(int i = 0;i<c->constInputKeys().size();i++)
  {
    c->fillConstInputsPrm(i,dd.m_constInputs.at(i).prm);
  }

  for(int i = 0;i<c->varInputsKeys().size();i++)
  {
    c->fillVarInputsPrm(i,dd.m_varInputs.at(i).prm);
  }
  return c;
}

void CurveUsrVcmd::init()
{
  //设置单位
  //增加变量曲线，常量曲线读取 keyName
  addUnit("rpm",1);
  addUnit("rps",0.0167);
  addUnit("rad.s",0.1047);
  addVarInputByName(VAR_KEYNAME_CTL_SPD_REF); //对应输入通道 dd.m_varInputs.at(0).datas
  addConstInputByName(CON_KEYNAME_MOT_NOS);//对应输入值 dd.m_constInputs.at(0).constK
}

void CurveUsrVcmd::calculate()
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

QString CurveUsrVcmd::name()
{
  return QString("Vcmd");
}

QString CurveUsrVcmd::note()
{
  return tr("Target Velocity");
}

QString CurveUsrVcmd::pluginName()
{
  return "CurveUsrVcmd";
}

