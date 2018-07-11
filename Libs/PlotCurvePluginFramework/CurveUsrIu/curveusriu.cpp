﻿#include "curveusriu.h"
#include <QVector>
#include <ctkPluginContext.h>
#include <QDebug>

#define VAR_KEYNAME_CUR_ADC_IA          "gSevDrv.sev_obj.cur.adc.ia"
#define CON_KEYNAME_MOT_IMAX            "gSevDrv.sev_obj.cur.mot.Imax_1"

CurveUsrIu::CurveUsrIu()
{

}

CurveUsrIu::CurveUsrIu(ctkPluginContext *context)
{
  qDebug()<<"CurveUsrIu construct";
  ctkDictionary dic;
  dic.insert("name","CurveUsrIu");
  context->registerService<ICurve>(this,dic);
}

ICurve *CurveUsrIu::clone()
{
  ICurve *c=new CurveUsrIu();
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

void CurveUsrIu::init()
{
  //设置单位
  //增加变量曲线，常量曲线读取 keyName
  addUnit("A",1);
  addUnit("mA",1000);
  addUnit("10mA",100);
  addUnit("100mA",10);
  addVarInputByName(VAR_KEYNAME_CUR_ADC_IA); //对应输入通道 dd.m_varInputs.at(0).datas
  addConstInputByName(CON_KEYNAME_MOT_IMAX);//对应输入值 dd.m_constInputs.at(0).constK
}

void CurveUsrIu::calculate()
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

QString CurveUsrIu::name()
{
  return QString("Iu");
}

QString CurveUsrIu::note()
{
  return tr("Current Iu");
}

QString CurveUsrIu::pluginName()
{
  return "CurveUsrIu";
}

