#include "curveusrtq.h"
#include <QVector>
#include <ctkPluginContext.h>
#include <QDebug>

#define VAR_KEYNAME_CUR_CTL_IQ          "gSevDrv.sev_obj.cur.ctl.iq"
#define CON_KEYNAME_MOT_IMAX            "gSevDrv.sev_obj.cur.mot.Imax_1"
#define CON_KEYNAME_MOT_PHIM            "gSevDrv.sev_obj.cur.mot.PHIm_1"

CurveUsrTq::CurveUsrTq()
{

}

CurveUsrTq::CurveUsrTq(ctkPluginContext *context)
{
  qDebug()<<"CurveUsrTq construct";
  ctkDictionary dic;
  dic.insert("name","CurveUsrTq");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveUsrTq::clone()
{
  ICurve *c=new CurveUsrTq();
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

void CurveUsrTq::init()
{
  //设置单位
  //增加变量曲线，常量曲线读取 keyName
  addUnit("N.m",1);
  addUnit("mN.m",1000);
  addVarInputByName(VAR_KEYNAME_CUR_CTL_IQ); //对应输入通道 dd.m_varInputs.at(0).datas
  addConstInputByName(CON_KEYNAME_MOT_IMAX);//对应输入值 dd.m_constInputs.at(0).constK
  addConstInputByName(CON_KEYNAME_MOT_PHIM);//对应输入值 dd.m_constInputs.at(1).constK
}

void CurveUsrTq::calculate()
{
  double result = 0;
  double imax = dd.m_constInputs.at(0).constK;
  double phmi = dd.m_constInputs.at(1).constK;
//  nos = 5000;
  dd.m_cData.values.clear();
  for(int i = 0;i<dd.m_varInputs.at(0).datas.size();i++)
  {
    result = (dd.m_varInputs.at(0).datas.at(i)/15000.0)*imax*0.1*phmi*0.001435;
    dd.m_cData.values.append(result);
//    qDebug()<<QString("vcmd %1 cal: in = %2,out = %3").arg(dd.m_axisInx).arg(dd.m_varInputs.at(0).datas.at(i)).arg(result);
  }

}

QString CurveUsrTq::name()
{
  return QString("Tq");
}

QString CurveUsrTq::note()
{
  return tr("Torque");
}

QString CurveUsrTq::pluginName()
{
  return "CurveUsrTq";
}

