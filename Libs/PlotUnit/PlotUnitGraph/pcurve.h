#ifndef PCURVE_H
#define PCURVE_H

#include <QObject>
class CurveData
{
public:
  CurveData(){}
  QVector<double>m_outPuts;
  QVector<double>m_times;
};

class CurveConst
{
public:
  QString m_keyName;
  int m_bytes;
  quint16 m_offtAddr;
  quint16 m_baseAddr;
  double m_constK;
};
class CurveVar
{
public:
  QString m_keyName;
  int m_bytes;
  quint16 m_offtAddr;
  quint16 m_baseAddr;
  QVector<double> m_datas;
};

class ICurveHandler;
class PCurve : public QObject
{
  Q_OBJECT
public:
  explicit PCurve(QObject *parent = 0);
  int m_rowInx;
  int m_axisInx;
  int m_dspInx;
  int m_devInx;
  QString m_devName;

  bool m_isDraw;
  QString m_fullName;
  QString m_shortName;

  double m_k;
  QList<CurveConst>m_constInputs;
  QList<CurveVar>m_varInputs;
  CurveData m_data;
  ICurveHandler *m_handler;

signals:

public slots:

};

#endif // PCURVE_H
