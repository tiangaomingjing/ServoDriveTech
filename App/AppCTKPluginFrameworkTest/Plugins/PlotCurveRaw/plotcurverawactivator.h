#ifndef PLOTCURVERAWACTIVATOR_H
#define PLOTCURVERAWACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class IPlotCurve;
class PlotCurveRawActivator : public QObject,public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "PlotCurve")
public:
  explicit PlotCurveRawActivator();
  void start(ctkPluginContext *context) Q_DECL_OVERRIDE;
  void stop(ctkPluginContext *context) Q_DECL_OVERRIDE;

signals:

public slots:

private:
  IPlotCurve *m_iPlotCurve;
};

#endif // PLOTCURVERAWACTIVATOR_H
