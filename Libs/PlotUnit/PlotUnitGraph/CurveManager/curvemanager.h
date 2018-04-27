#ifndef CURVEMANAGER_H
#define CURVEMANAGER_H

#include <QObject>
#include "comglobal.h"

class ICurve;
class DevSamplePrm
{
public:
  QList<ComDriver::PlotControlPrm> m_prms;
  int m_devInx;
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

  QList<DevSamplePrm> samplPrms();

  int sampleScale() const;
  void setSampleScale(int sampleScale);

signals:

public slots:

private:
  QList<ICurve *> m_curveList;
  QList<QColor>m_colorDefault;
  QList<DevSamplePrm> m_samplPrms;//每一个设备保存一个采样控制参数

  int m_sampleScale;//采样倍数 实际的采样时间=m_sampleScale*62.5us
};

#endif // CURVEMANAGER_H
