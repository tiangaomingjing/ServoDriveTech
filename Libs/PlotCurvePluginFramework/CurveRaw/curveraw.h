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

  QString name() Q_DECL_OVERRIDE {return QString("");}
  QString note() Q_DECL_OVERRIDE {return QString("");}
};

#endif // CURVERAW_H
