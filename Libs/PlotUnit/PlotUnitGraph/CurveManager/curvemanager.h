#ifndef CURVEMANAGER_H
#define CURVEMANAGER_H

#include <QObject>
#include "comglobal.h"
#define CURVE_MAX_NUM           16

class ICurve;
class SevDevice;

class DevSamplePrm
{
public:
  QList<ComDriver::PlotControlPrm> m_prms;
  int m_devInx;
};

class DSPCurves
{
public:
  int m_dspInx;
  QList<ICurve *>m_curves;
};

class DevCurves
{
public:
  int m_devInx;
  QList<DSPCurves>m_dspCurves;
};


class CurveManager : public QObject
{
  Q_OBJECT
public:
  explicit CurveManager(QObject *parent = 0);
  ~CurveManager();

  QList<ICurve *> curveList() const;
  void addCurve(ICurve *curve);
  void removeCurve(ICurve *curve);
  void removeCurve(int inx);
  void clearCurve();

  int varCurveTotalCount();

  QColor color(int totalCount) const;



  int sampleScale() const;
  void setSampleScale(int sampleScale);

  int storeTime() const;
  void setStoreTime(int storeTimeS);

  void updateSamplPrms();
  QList<DevCurves> devCurves() const;
  QList<DevSamplePrm> samplPrms() const;

  bool isOverMaxCurveSizeWhenAdd(ICurve *c);

  bool checkCurveInSevDevice(SevDevice *dev,ICurve *c);
  updateCurveCtlPrmsFromDevice(SevDevice *dev ,ICurve *c);

signals:

public slots:

private:
  QList<ICurve *> m_curveList;
  QList<QColor>m_colorDefault;
  QList<DevSamplePrm> m_samplPrms;//每一个设备保存一个采样控制参数
  QList<DevCurves>m_devCurves;

  int m_sampleScale;//采样倍数 实际的采样时间=m_sampleScale*62.5us
  int m_storeTimeS;//s
};

#endif // CURVEMANAGER_H
