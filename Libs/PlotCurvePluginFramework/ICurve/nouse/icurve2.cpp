#include "icurve.h"
#include <QHash>
#include <QVector>


ICurve::~ICurve()
{

}

void ICurve::prepare()
{
  setName(name());
  setNote(note());
  init();
  m_sData.keys.append(0);
  m_sData.values.append(0);
  m_k=1;
}

void ICurve::exec()
{
  calculate();
  adjustData();
}

void ICurve::setName(const QString &name)
{
  m_name=name;
}

void ICurve::setNote(const QString &note)
{
  m_note=note;
}

QString ICurve::displayName()
{
  return QObject::tr("%1.%2").arg(m_name).arg(m_unitName);
}

QString ICurve::fullName()
{
  return QObject::tr("%1.%2.%3").arg(name()).arg(note()).arg(m_unitName);
}


void ICurve::fillConstInputsPrm(int inx, const CurvePrm &prm)
{
  if(inx<m_constInputs.size())
    m_constInputs[inx].prm=prm;
}

void ICurve::fillVarInputsPrm(int inx, const CurvePrm &prm)
{
  if(inx<m_varInputs.size())
    m_varInputs[inx].prm=prm;
}

void ICurve::setConstInputK(int channel, double value)
{
  if(channel<m_constInputs.size())
  {
    m_constInputs[channel].constK=value;
  }
}
/**
 * @brief ICurve::varInputVector 传的是引用，操作引用 ，就相当操作原来的数
 * @param channel
 * @return
 */
QVector<double> &ICurve::varInputVector(int channel)
{
  if(channel<m_varInputs.size())
    return m_varInputs[channel].datas;
  else
    return m_varInputs[0].datas;
}

int ICurve::rowInx() const
{
  return m_rowInx;
}

void ICurve::setRowInx(int rowInx)
{
  m_rowInx = rowInx;
  m_dspInx = rowInx/2;
}

int ICurve::devInx() const
{
  return m_devInx;
}

void ICurve::setDevInx(int devInx)
{
  m_devInx = devInx;
}

QString ICurve::devName() const
{
  return m_devName;
}

void ICurve::setDevName(const QString &devName)
{
  m_devName = devName;
}

double ICurve::samplInterval() const
{
  return m_samplInterval;
}

void ICurve::setSamplInterval(double samplInterval)
{
  m_samplInterval = samplInterval;
}

void ICurve::adjustData()
{
  //乘以单位
  for(int i=0;i<m_cData.values.size();i++)
  {
    double v=m_cData.values.at(i)*m_k;
    m_cData.values.replace(i,v);
  }
  m_sData.values.append(m_cData.values);

  quint32 size=m_cData.values.size();
  quint32 t;
  for(quint32 i=0;i<size;i++)
  {
    t=m_sData.keys.last()+i*m_samplInterval*0.001;//坐标ms显示
    m_sData.keys.append(t);
  }

  qint32 overSize=m_sData.values.size()- m_storePointCount;
  m_sData.keys.remove(0,overSize);
  m_sData.values.remove(0,overSize);
}

void ICurve::setStorePointCount(qint32 storePointCount)
{
  m_storePointCount = storePointCount;
}

QStringList ICurve::constInputKeys()
{
  QStringList list;
  for(int i=0;i<m_constInputs.size();i++)
    list.append(m_constInputs.at(i).keyName);
  return list;
}

QStringList ICurve::varInputsKeys()
{
  QStringList list;
  for(int i=0;i<m_varInputs.size();i++)
    list.append(m_varInputs.at(i).keyName);
  return list;
}

void ICurve::addConstInputByName(const QString &name)
{
  CurveConst constPrm;
  constPrm.keyName=name;
  m_constInputs.append(constPrm);
}

void ICurve::addVarInputByName(const QString &name)
{
  CurveVar var;
  var.keyName=name;
  m_varInputs.append(var);
}

void ICurve::addUnit(const QString &uName, double k)
{
  m_units.insert(uName,k);
}

void ICurve::setUnit(const QString &uName)
{
  if(m_units.contains(uName))
  {
    m_unitName=uName;
    m_k=m_units.value(uName);
  }
}

double ICurve::curUnitK()
{
  return m_k;
}

QString ICurve::curUnitName()
{
  return m_unitName;
}

QStringList ICurve::unitNames()
{
  return QStringList(m_units.keys());
}
