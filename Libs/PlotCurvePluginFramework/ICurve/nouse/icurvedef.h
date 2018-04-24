#ifndef ICURVEDEF
#define ICURVEDEF
#include <QObject>
#include <QVector>
#include <QHash>
#include <QColor>
#include <QList>
class CurveData
{
public:
  CurveData(){}
  QVector<double>values;
  QVector<double>keys;
};

class CurvePrm
{
public:
  CurvePrm(){}
  quint16 bytes;
  quint16 offtAddr;
  quint16 baseAddr;
};

class CurveConst
{
public:
  QString keyName;
  CurvePrm prm;
  double constK;
};
class CurveVar
{
public:
  QString keyName;
  CurvePrm prm;
  QVector<double>datas;
};

#endif // ICURVEDEF

