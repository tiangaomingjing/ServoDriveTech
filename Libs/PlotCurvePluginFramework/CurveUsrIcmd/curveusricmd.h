#ifndef CURVEUSRICMD_H
#define CURVEUSRICMD_H
#include <QObject>
#include "icurve.h"

class ctkPluginContext;

class  CurveUsrIcmd:public QObject,public ICurve
{
  Q_OBJECT
  Q_INTERFACES(ICurve)
public:
  CurveUsrIcmd();
  CurveUsrIcmd(ctkPluginContext *context);

  ICurve *clone() Q_DECL_OVERRIDE ;
  void init() Q_DECL_OVERRIDE ;

  void calculate() Q_DECL_OVERRIDE ;

  QString name() Q_DECL_OVERRIDE ;
  QString note() Q_DECL_OVERRIDE ;

};

#endif // CURVEUSRICMD_H
