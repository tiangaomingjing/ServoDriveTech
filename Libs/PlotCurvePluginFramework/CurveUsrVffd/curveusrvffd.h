#ifndef CURVEUSRVFFD_H
#define CURVEUSRVFFD_H
#include <QObject>
#include "icurve.h"

class ctkPluginContext;

class  CurveUsrVffd:public QObject,public ICurve
{
  Q_OBJECT
  Q_INTERFACES(ICurve)
public:
  CurveUsrVffd();
  CurveUsrVffd(ctkPluginContext *context);

  ICurve *clone() Q_DECL_OVERRIDE ;
  void init() Q_DECL_OVERRIDE ;
  void reset() Q_DECL_OVERRIDE ;

  void calculate() Q_DECL_OVERRIDE ;

  QString name() Q_DECL_OVERRIDE ;
  QString note() Q_DECL_OVERRIDE ;
  QString pluginName() Q_DECL_OVERRIDE ;

};

#endif // CURVEUSRVFFD_H
