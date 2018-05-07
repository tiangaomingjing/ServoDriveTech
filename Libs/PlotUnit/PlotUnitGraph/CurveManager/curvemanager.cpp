#include "curvemanager.h"
#include "icurve.h"
#include "gtutils.h"
#include "sdtglobaldef.h"

#include <QMultiHash>
#include <QDebug>

#define CURVE_MANAGER_TEST 1

CurveManager::CurveManager(QObject *parent) : QObject(parent),
  m_sampleScale(1)
{
  //----设置好默认颜色------------
  m_colorDefault.append(QColor(Qt::red));
  m_colorDefault.append(QColor(Qt::green));
  m_colorDefault.append(QColor(Qt::blue));
  m_colorDefault.append(QColor(Qt::black));

  m_colorDefault.append(QColor(255,0,255));
  m_colorDefault.append(QColor(0,170,0));
  m_colorDefault.append(QColor(0,170,255));
  m_colorDefault.append(QColor(170,0,255));
  m_colorDefault.append(QColor(170,0,0));
  m_colorDefault.append(QColor(255,170,127));
}

CurveManager::~CurveManager()
{

}

QList<ICurve *> CurveManager::curveList() const
{
  return m_curveList;
}

void CurveManager::addCurve(ICurve *curve)
{
  m_curveList.append(curve);
}

void CurveManager::removeCurve(ICurve *curve)
{
  m_curveList.removeOne(curve);
  delete curve;
}

void CurveManager::removeCurve(int inx)
{
  if(inx<m_curveList.count())
  {
    ICurve *curve=m_curveList.at(inx);
    m_curveList.removeAt(inx);
    delete curve;
  }
}

void CurveManager::clearCurve()
{
  GT::deepClearList(m_curveList);
}

int CurveManager::varCurveTotalCount()
{
  int num=0;
  ICurve *curve;
  for(int i=0;i<m_curveList.count();i++)
  {
    curve=m_curveList.at(i);
    num+=curve->varInputsKeys().size();
  }
  return num;
}

QColor CurveManager::color(int totalCount) const
{
  return m_colorDefault.at(totalCount%m_colorDefault.size());
}

QList<DevSamplePrm> CurveManager::samplPrms() const
{
  return m_samplPrms;
}

int CurveManager::sampleScale() const
{
  return m_sampleScale;
}

void CurveManager::setSampleScale(int sampleScale)
{
  m_sampleScale = sampleScale;
  for(int i=0;i<m_curveList.size();i++)
  {
    ICurve *c=m_curveList.at(i);
    c->setSamplInterval(m_sampleScale);
  }
}

int CurveManager::storeTime() const
{
  return m_storeTimeS;
}

void CurveManager::setStoreTime(int storeTimeS)
{
  m_storeTimeS = storeTimeS;
  double s=storeTimeS*1000000/SAMPLING_INTERVAL_US ;
  for(int i=0;i<m_curveList.size();i++)
  {
    ICurve *c=m_curveList.at(i);
    c->setStorePointCount(s);
  }

}

void CurveManager::updateSamplPrms()
{
  m_samplPrms.clear();
  m_devCurves.clear();

  //找到采样的设备ID
  QList<int> devs;
  for(int i=0;i<m_curveList.size();i++)
  {
    int dev=m_curveList.at(i)->devInx();
    if(devs.isEmpty())
    {
      devs.append(dev);
    }
    else
    {
      bool has=false;
      for(int j=0;j<devs.size();j++)
      {
        if(dev==devs.at(j))
        {
          has=true;
          break;
        }
      }
      if(has==false)
        devs.append(dev);
    }
  }

  //设备归类
  QMultiHash<int ,ICurve *> multiHashDev;
  for(int i=0;i<m_curveList.size();i++)
  {
    ICurve *curve=m_curveList.at(i);
    multiHashDev.insert(curve->devInx(),curve);
  }

#if CURVE_MANAGER_TEST
  if(devs.size()>0)
    qDebug()<<"device total size"<<devs.size()<<"hashDev value(0) size"<<multiHashDev.values(0).size();
#endif

  for(int i=0;i<devs.size();i++)
  {
    QList<ICurve *>curves;
    ICurve *c;
    DevSamplePrm devPrm;
    DevCurves devCurves;
    devPrm.m_devInx=devs.at(i);
    devCurves.m_devInx=devs.at(i);
    curves=multiHashDev.values(devPrm.m_devInx);//这个设备下所有的曲线
    qDebug()<<"at device "<<devPrm.m_devInx<<"curves total size"<<curves.size();

    //找出DSP 0 1 2
    QList<int> dsps;
    for(int i=0;i<curves.size();i++)
    {
      int d=curves.at(i)->dspInx();
      qDebug()<<"ddddddddddddddddddd "<<d;
      if(dsps.isEmpty())
      {
        dsps.append(d);
        qDebug()<<"append "<<d;
      }
      else
      {
        bool has=false;
        for(int j=0;j<dsps.size();j++)
        {
          if(d==dsps.at(j))
          {
            has=true;
            break;
          }
        }
        if(has==false)
        {
          dsps.append(d);
          qDebug()<<"append "<<d;
        }
      }
    }

#if CURVE_MANAGER_TEST
  for(int i=0;i<dsps.size();i++)
  {
    qDebug()<<"dsp "<<dsps.at(i);
  }
#endif

    //DSP归类
    QMultiHash<int ,ICurve *> multiHashDSP;
    for(int j=0;j<curves.size();j++)
    {
      int dspInx;
      c=curves.at(j);
      dspInx=c->dspInx();
      multiHashDSP.insert(dspInx,c);
    }

    for(int i=0;i<dsps.size();i++)
    {
      int dspInx =0;
      QList<ICurve *> curvesInDsp;
      dspInx=dsps.at(i);
      curvesInDsp=multiHashDSP.values(dspInx);//单个DSP下面的所有曲线
      qDebug()<<"dspinx"<<dspInx<<"curvesInDsp.size = "<<curvesInDsp.size();

      DSPCurves dspCurves;
      dspCurves.m_dspInx=dspInx;

      ComDriver::PlotControlPrm prm;

      prm.dspIndex = dspInx;
      prm.enable = ComDriver::PLOT_DISABLE;
      prm.samplingScale = m_sampleScale;
      prm.number = 0;

      for(int j=0;j<curvesInDsp.size();j++)
      {
        ICurve *c=curvesInDsp.at(j);
        dspCurves.m_curves.append(c);

        int varSize = c->varInputsKeys().size();
        qDebug()<<"varSize "<<varSize;
        for(int k=0;k<varSize;k++)
        {
          ComDriver::PlotCurveInfo info;
          const CurvePrm *curvePrm=&(c->varInputs().at(k).prm);
          info.base = curvePrm->baseAddr;
          info.bytes = curvePrm->bytes;
          info.ofst = curvePrm->offtAddr;
          prm.curveInfo.push_back(info);
        }
        prm.number = prm.number + varSize;
      }

      devPrm.m_prms.append(prm);
      devCurves.m_dspCurves.append(dspCurves);
    }

    m_samplPrms.append(devPrm);
    m_devCurves.append(devCurves);
  }

#if CURVE_MANAGER_TEST
  for(int i=0;i<m_samplPrms.size();i++)
  {
    const DevSamplePrm *dev=&(m_samplPrms.at(i));
    qDebug()<<"Device = "<<i<<" plot prms is:";
    for(int j=0;j<dev->m_prms.size();j++)
    {
      const ComDriver::PlotControlPrm *prm=&(dev->m_prms.at(j));
      qDebug()<<QString("dspIndex = %1 ,curve number = %2 ,samplScale = %3").arg(prm->dspIndex).arg(prm->number).arg(prm->samplingScale);

      for(int k=0;k<(int)prm->curveInfo.size();k++)
      {
        const ComDriver::PlotCurveInfo *info=&(prm->curveInfo.at(k));
        qDebug()<<QString("base = %1 , bytes = %2 , ofst = %3").arg(info->base).arg(info->bytes).arg(info->ofst);
      }
    }
  }

  qDebug()<<"show dspcurve";
  for(int i=0;i<m_devCurves.size();i++)
  {
    qDebug()<<"at device ="<<m_devCurves.at(i).m_devInx;
    for(int j=0;j<m_devCurves.at(i).m_dspCurves.size();j++)
    {
      qDebug()<<"at dsp = "<<m_devCurves.at(i).m_dspCurves.at(j).m_dspInx;
      for(int k=0;k<m_devCurves.at(i).m_dspCurves.at(j).m_curves.size();k++)
      {
        qDebug()<<"curve ="<<m_devCurves.at(i).m_dspCurves.at(j).m_curves.at(k)->fullName()<<"offset"<<m_devCurves.at(i).m_dspCurves.at(j).m_curves.at(k)->varInputs().at(0).prm.offtAddr;
      }
    }
  }
#endif
}

QList<DevCurves> CurveManager::devCurves() const
{
  return m_devCurves;
}

