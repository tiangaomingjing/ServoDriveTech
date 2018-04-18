#ifndef PLOTCURVEUSRPOS_H
#define PLOTCURVEUSRPOS_H

#include <QObject>
#include "iplotcurve.h"

class ctkPluginContext;

class PlotCurveUsrPos : public QObject ,public IPlotCurve
{
  Q_OBJECT
  Q_INTERFACES(IPlotCurve)
public:
  explicit PlotCurveUsrPos(ctkPluginContext *context);
  void sayHello() Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // PLOTCURVEUSRPOS_H
