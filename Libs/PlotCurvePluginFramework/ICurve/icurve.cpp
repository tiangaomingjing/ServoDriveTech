#include "icurve.h"
#include <QHash>
#include <QVector>
#include <QDebug>


ICurve::~ICurve()
{

}
/**
 * @brief ICurve::prepare
 * 客户端使用时，新建对象后须先调用prepare函数进行初始化
 */
void ICurve::prepare()
{
  setName(name());
  setNote(note());
  init();
}

void ICurve::exec()
{
  updateCurrentTime();
  calculate();
  adjustData();
}

void ICurve::setName(const QString &name)
{
  dd.m_name=name;
}

void ICurve::setNote(const QString &note)
{
  dd.m_note=note;
}

QString ICurve::displayName()
{
  return QObject::tr("%1.%2").arg(dd.m_name).arg(dd.m_unitName);
}

QString ICurve::fullName()
{
  return QObject::tr("%1.%2.%3").arg(name()).arg(note()).arg(dd.m_unitName);
}


void ICurve::fillConstInputsPrm(int inx, const CurvePrm &prm)
{
  if(inx<dd.m_constInputs.size())
   dd.m_constInputs[inx].prm=prm;
}

void ICurve::fillVarInputsPrm(int inx, const CurvePrm &prm)
{
  if(inx<dd.m_varInputs.size())
    dd.m_varInputs[inx].prm=prm;
}

void ICurve::setConstInputK(int channel, double value)
{
  if(channel<dd.m_constInputs.size())
  {
    dd.m_constInputs[channel].constK=value;
  }
}

void ICurve::setVarInputVector(int channel, const QVector<double> &in)
{
  if(channel<dd.m_varInputs.size())
  {
    dd.m_varInputs[channel].datas.clear();
    dd.m_varInputs[channel].datas.append(in);
  }
}

int ICurve::devInx() const
{
  return dd.m_devInx;
}

void ICurve::setDevInx(int devInx)
{
  dd.m_devInx = devInx;
}

QString ICurve::devName() const
{
  QByteArray byte;
  byte.append(65+dd.m_devInx);
  return QString::fromLatin1(byte);
}

double ICurve::samplInterval() const
{
  return dd.m_samplInterval;
}

void ICurve::setSamplInterval(int samplIntervalScale)
{
  dd.m_samplInterval = samplIntervalScale*SAMPLING_INTERVAL_US*0.000001;
  dd.m_currentTime = 0;
  dd.m_cData.keys.clear();
  dd.m_cData.values.clear();
  dd.m_sData.keys.clear();
  dd.m_sData.values.clear();
}

void ICurve::adjustData()
{
  //乘以单位
  for(int i=0;i<dd.m_cData.values.size();i++)
  {
    double v=dd.m_cData.values.at(i)*dd.m_k;
    dd.m_cData.values.replace(i,v);
  }
  dd.m_sData.values.append(dd.m_cData.values);


  qint32 overSize=dd.m_sData.values.size()- dd.m_storePointCount;
  if(overSize>0)
  {
//    dd.m_sData.keys.remove(0,overSize);
    dd.m_sData.values.remove(0,overSize);
//    qDebug()<<"store data size = "<<dd.m_sData.values.size();
  }
}

void ICurve::updateCurrentTime()
{
  quint32 size=dd.m_varInputs.at(0).datas.size();
//  qDebug()<<"curve size"<<size;

  dd.m_cData.keys.clear();
  for(quint32 i=0;i<size;i++)
  {
    dd.m_currentTime = dd.m_currentTime+dd.m_samplInterval;//坐标s显示
//    dd.m_sData.keys.append(dd.m_currentTime);
    dd.m_cData.keys.append(dd.m_currentTime);
  }
//  qDebug()<<"dd.m_currentTime"<<dd.m_currentTime;
}

void ICurve::setStorePointCount(quint32 storePointCount)
{
  dd.m_storePointCount = storePointCount;
}

int ICurve::axisInx() const
{
    return dd.m_axisInx;
}

void ICurve::setAxisInx(int axisInx)
{
    dd.m_axisInx = axisInx;
    dd.m_dspInx = axisInx/2;
}

QColor ICurve::color() const
{
  return dd.m_color;
}

void ICurve::setColor(const QColor &color)
{
  dd.m_color = color;
}

bool ICurve::isDraw() const
{
  return  dd.m_isDraw;
}

void ICurve::setIsDraw(bool isDraw)
{
  dd.m_isDraw = isDraw;
}

QList<CurveVar> &ICurve::varInputs()
{
  return dd.m_varInputs;
}


QList<CurveConst> &ICurve::constInputs()
{
  return dd.m_constInputs;
}

int ICurve::dspInx() const
{
  return dd.m_dspInx;
}

void ICurve::setDspInx(int dspInx)
{
  dd.m_dspInx = dspInx;
}

void ICurve::setAxisCount(int axisCount)
{
  dd.m_axisCount = axisCount;
}

int ICurve::axisCount() const
{
  return dd.m_axisCount;
}

CurveData *ICurve::cData()
{
  return &(dd.m_cData);
}

CurveData *ICurve::sData()
{
  return &(dd.m_sData);
}

void ICurve::savePrepare()
{
  dd.m_sData.keys.clear();
  for(int i = dd.m_sData.values.size();i >0; i--)
  {
    double time = dd.m_currentTime - dd.m_samplInterval*i;
    dd.m_sData.keys.append(time);
  }
}

QString ICurve::pluginName() const
{
  return dd.m_pluginName;
}

void ICurve::setPluginName(const QString &name)
{
  dd.m_pluginName = name;
}

QStringList ICurve::constInputKeys()
{
  QStringList list;
  for(int i=0;i<dd.m_constInputs.size();i++)
    list.append(dd.m_constInputs.at(i).keyName);
  return list;
}

QStringList ICurve::varInputsKeys()
{
  QStringList list;
  for(int i=0;i<dd.m_varInputs.size();i++)
    list.append(dd.m_varInputs.at(i).keyName);
  return list;
}

void ICurve::addConstInputByName(const QString &name)
{
  CurveConst constPrm;
  constPrm.keyName=name;
  dd.m_constInputs.append(constPrm);
}

void ICurve::addVarInputByName(const QString &name)
{
  CurveVar var;
  var.keyName=name;
  dd.m_varInputs.append(var);
}

void ICurve::addUnit(const QString &uName, double k)
{
  dd.m_units.insert(uName,k);
  for(int i = 0;i<dd.m_unitNameList.size();i++)
  {
    if(dd.m_unitNameList.at(i) != uName)
      dd.m_unitNameList.append(uName);
  }
}

void ICurve::setUnit(const QString &uName)
{
  if(dd.m_units.contains(uName))
  {
    dd.m_unitName=uName;
    dd.m_k=dd.m_units.value(uName);
  }
}

double ICurve::curUnitK()
{
  return dd.m_k;
}

QString ICurve::curUnitName()
{
  return dd.m_unitName;
}

QStringList ICurve::unitNames()
{
  return dd.m_unitNameList;
}

ICurve::ICurvePrivate::ICurvePrivate()
{
  m_sData.keys.append(0);
  m_sData.values.append(0);
  m_k = 1;
  m_isDraw=true;
  m_color=QColor(Qt::black);
  m_currentTime = 0;
  m_samplInterval=62.5*0.000001;
  m_storePointCount=10*1000000/62.5;
  m_axisCount = 4;
}
