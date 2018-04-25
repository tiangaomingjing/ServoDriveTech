#ifndef ICURVE_P
#define ICURVE_P
#include "icurvedef.h"
#include "icurve.h"
class ICurvePrivate
{
public:
  virtual ~ICurvePrivate(){}
  int m_rowInx;
  int m_axisInx;
  int m_dspInx;
  int m_devInx;
  QString m_devName;

  bool m_isDraw;
  QColor m_color;
  QString m_name;
  QString m_note;
  QString m_unitName;

  double m_k;
  double m_samplInterval;//us
  qint32 m_storePointCount;

  QList<CurveConst>m_constInputs;
  QList<CurveVar>m_varInputs;
  QHash<QString,double> m_units;

  CurveData m_cData;
  CurveData m_sData;

  QString m_pluginName;
};

#endif // ICURVE_P

