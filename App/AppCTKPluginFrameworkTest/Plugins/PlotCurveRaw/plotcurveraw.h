#ifndef PLOTCURVERAW_H
#define PLOTCURVERAW_H

#include <QObject>
#include "iplotcurve.h"

class ctkPluginContext;

class PlotCurveRaw : public QObject ,public IPlotCurve
{
  Q_OBJECT
  Q_INTERFACES(IPlotCurve)
public:
  explicit PlotCurveRaw(ctkPluginContext *context);
  void sayHello() Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // PLOTCURVERAW_H
