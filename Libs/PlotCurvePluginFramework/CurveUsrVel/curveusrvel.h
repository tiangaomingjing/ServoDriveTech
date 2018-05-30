﻿#ifndef CURVEUSRVEL_H
#define CURVEUSRVEL_H
#include <QObject>
#include "icurve.h"

class ctkPluginContext;

class  CurveUsrVel:public QObject,public ICurve
{
  Q_OBJECT
  Q_INTERFACES(ICurve)
public:
  CurveUsrVel();
  CurveUsrVel(ctkPluginContext *context);

  ICurve *clone() Q_DECL_OVERRIDE ;
  void init() Q_DECL_OVERRIDE ;

  void calculate() Q_DECL_OVERRIDE ;

  QString name() Q_DECL_OVERRIDE ;
  QString note() Q_DECL_OVERRIDE ;
  QString pluginName() Q_DECL_OVERRIDE ;

};

#endif // CURVEUSRVEL_H