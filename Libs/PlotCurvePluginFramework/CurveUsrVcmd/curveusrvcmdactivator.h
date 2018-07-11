#ifndef CURVEUSRVCMDACTIVATOR_H
#define CURVEUSRVCMDACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class ICurve;

class CurveUsrVcmdActivator : public QObject,public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "CurveUsrVcmd")
public:
  explicit CurveUsrVcmdActivator();
  void start(ctkPluginContext *context) Q_DECL_OVERRIDE;
  void stop(ctkPluginContext *context) Q_DECL_OVERRIDE;

signals:

public slots:
private:
  ICurve *m_iCurve;
};

#endif // CURVEUSRVCMDACTIVATOR_H
