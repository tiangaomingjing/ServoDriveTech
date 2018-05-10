#ifndef CURVEUSRPOSACTIVATOR_H
#define CURVEUSRPOSACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class ICurve;

class CurveUsrPosActivator : public QObject,public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "CurveUsrPos")
public:
  explicit CurveUsrPosActivator();
  void start(ctkPluginContext *context) Q_DECL_OVERRIDE;
  void stop(ctkPluginContext *context) Q_DECL_OVERRIDE;

signals:

public slots:
private:
  ICurve *m_iCurve;
};

#endif // CURVEUSRPOSACTIVATOR_H
