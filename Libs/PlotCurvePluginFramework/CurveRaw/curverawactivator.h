﻿#ifndef CURVERAWACTIVATOR_H
#define CURVERAWACTIVATOR_H

#include <QObject>
#include <ctkPluginActivator.h>

class ICurve;

class CurveRawActivator : public QObject,public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)
  Q_PLUGIN_METADATA(IID "CurveRaw")
public:
  explicit CurveRawActivator();
  void start(ctkPluginContext *context) Q_DECL_OVERRIDE;
  void stop(ctkPluginContext *context) Q_DECL_OVERRIDE;

signals:

public slots:
private:
  ICurve *m_iCurve;
};

#endif // CURVERAWACTIVATOR_H
