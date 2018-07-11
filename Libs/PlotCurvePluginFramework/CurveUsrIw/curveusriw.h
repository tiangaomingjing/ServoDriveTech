﻿#ifndef CURVEUSRIW_H
#define CURVEUSRIW_H
#include <QObject>
#include "icurve.h"

class ctkPluginContext;

class  CurveUsrIw:public QObject,public ICurve
{
  Q_OBJECT
  Q_INTERFACES(ICurve)
public:
  CurveUsrIw();
  CurveUsrIw(ctkPluginContext *context);

  ICurve *clone() Q_DECL_OVERRIDE ;
  void init() Q_DECL_OVERRIDE ;
  void reset() {}

  void calculate() Q_DECL_OVERRIDE ;

  QString name() Q_DECL_OVERRIDE ;
  QString note() Q_DECL_OVERRIDE ;
  QString pluginName() Q_DECL_OVERRIDE ;

};

#endif // CURVEUSRIW_H
