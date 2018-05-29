#ifndef CURVERAW_H
#define CURVERAW_H
#include <QObject>
#include "icurve.h"

class ctkPluginContext;

class  CurveRaw:public QObject,public ICurve
{
  Q_OBJECT
  Q_INTERFACES(ICurve)
public:
  CurveRaw();
  CurveRaw(ctkPluginContext *context);

  ICurve *clone() Q_DECL_OVERRIDE;
  void init() Q_DECL_OVERRIDE{}

  void calculate() Q_DECL_OVERRIDE;

  QString name() Q_DECL_OVERRIDE {return QString("abc");}
  QString note() Q_DECL_OVERRIDE {return QString("efg");}

  QString displayName() Q_DECL_OVERRIDE;
  QString fullName() Q_DECL_OVERRIDE;

  QString pluginName() Q_DECL_OVERRIDE;
};

#endif // CURVERAW_H
