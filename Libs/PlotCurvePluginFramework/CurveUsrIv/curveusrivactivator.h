#ifndef CURVEUSRIVACTIVATOR_H
#define CURVEUSRIVACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class ICurve;

class CurveUsrIvActivator : public QObject,public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "CurveUsrIv")
public:
  explicit CurveUsrIvActivator();
  void start(ctkPluginContext *context) Q_DECL_OVERRIDE;
  void stop(ctkPluginContext *context) Q_DECL_OVERRIDE;

signals:

public slots:
private:
  ICurve *m_iCurve;
};

#endif // CURVEUSRIVACTIVATOR_H
