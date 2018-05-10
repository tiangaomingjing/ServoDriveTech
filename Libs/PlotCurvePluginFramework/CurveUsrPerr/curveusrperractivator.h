#ifndef CURVEUSRPERRACTIVATOR_H
#define CURVEUSRPERRACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class ICurve;

class CurveUsrPerrActivator : public QObject,public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "CurveUsrPerr")
public:
  explicit CurveUsrPerrActivator();
  void start(ctkPluginContext *context) Q_DECL_OVERRIDE;
  void stop(ctkPluginContext *context) Q_DECL_OVERRIDE;

signals:

public slots:
private:
  ICurve *m_iCurve;
};

#endif // CURVEUSRPERRACTIVATOR_H
