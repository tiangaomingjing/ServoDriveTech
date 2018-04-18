#ifndef PLOTCURVEUSRPOSACTIVATOR_H
#define PLOTCURVEUSRPOSACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class IPlotCurve;
class PlotCurveUsrPosActivator : public QObject,public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "PlotCurveUsrPos")
public:
  explicit PlotCurveUsrPosActivator();
  void start(ctkPluginContext *context) Q_DECL_OVERRIDE;
  void stop(ctkPluginContext *context) Q_DECL_OVERRIDE;

signals:

public slots:

private:
  IPlotCurve *m_iPlotCurve;
};

#endif // PLOTCURVEUSRPOSACTIVATOR_H
