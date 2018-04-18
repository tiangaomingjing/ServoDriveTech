#ifndef IPLOTCURVE_H
#define IPLOTCURVE_H

#include <QObject>
#define IPlotCurve_iid "gt.plot.curve.iplotcurve"

class  IPlotCurve
{
public:

  virtual ~IPlotCurve();

  virtual void sayHello() = 0;
};

Q_DECLARE_INTERFACE(IPlotCurve,IPlotCurve_iid)
#endif // IPLOTCURVE_H
