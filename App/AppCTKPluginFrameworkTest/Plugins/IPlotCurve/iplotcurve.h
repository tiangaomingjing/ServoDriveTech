#ifndef IPLOTCURVE_H
#define IPLOTCURVE_H

#include <QObject>
#include <QVector>
#define IPlotCurve_iid "gt.plot.curve.iplotcurve"

class CurveData
{
public:
  CurveData(){}
  QVector<double>values;
  QVector<double>keys;
};

class  IPlotCurve
{
public:

  virtual ~IPlotCurve();

  virtual void sayHello() = 0;
  virtual IPlotCurve *clone() = 0;

  CurveData data;

};

Q_DECLARE_INTERFACE(IPlotCurve,IPlotCurve_iid)
#endif // IPLOTCURVE_H
