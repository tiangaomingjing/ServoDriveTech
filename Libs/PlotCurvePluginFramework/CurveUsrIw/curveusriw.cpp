#include "curveusriw.h"
#include <QVector>
#include <ctkPluginContext.h>
#include <QDebug>

#define VAR_KEYNAME_CUR_ADC_IC          "gSevDrv.sev_obj.cur.adc.ic"
#define CON_KEYNAME_MOT_IMAX            "gSevDrv.sev_obj.cur.mot.Imax_1"

CurveUsrIw::CurveUsrIw()
{

}

CurveUsrIw::CurveUsrIw(ctkPluginContext *context)
{
  qDebug()<<"CurveUsrIw construct";
  ctkDictionary dic;
  dic.insert("name","CurveUsrIw");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveUsrIw::clone()
{
  ICurve *c=new CurveUsrIw();
  c->prepare();
  return c;
}

void CurveUsrIw::init()
{
  //设置单位
  //增加变量曲线，常量曲线读取 keyName
  addUnit("A",1);
  addUnit("mA",1000);
  addUnit("10mA",100);
  addUnit("100mA",10);
  addVarInputByName(VAR_KEYNAME_CUR_ADC_IC); //对应输入通道 dd.m_varInputs.at(0).datas
  addConstInputByName(CON_KEYNAME_MOT_IMAX);//对应输入值 dd.m_constInputs.at(0).constK
}

void CurveUsrIw::calculate()
{
  double result = 0;
  double imax = dd.m_constInputs.at(0).constK;
//  nos = 5000;
  dd.m_cData.values.clear();
  for(int i = 0;i<dd.m_varInputs.at(0).datas.size();i++)
  {
    result = (dd.m_varInputs.at(0).datas.at(i)/15000.0)*imax*0.1;
    dd.m_cData.values.append(result);
//    qDebug()<<QString("vcmd %1 cal: in = %2,out = %3").arg(dd.m_axisInx).arg(dd.m_varInputs.at(0).datas.at(i)).arg(result);
  }

}

QString CurveUsrIw::name()
{
  return QString("Iw");
}

QString CurveUsrIw::note()
{
  return tr("Current Iw");
}

QString CurveUsrIw::pluginName()
{
  return "CurveUsrIw";
}

