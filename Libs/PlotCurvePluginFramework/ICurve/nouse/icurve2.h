#ifndef ICURVE_H
#define ICURVE_H

#include "icurve_global.h"
#include "icurve_p.h"
#define ICurve_iid "gt.plot.curve.icurve"

class QTreeWidgetItem;

class ICURVESHARED_EXPORT ICurve
{
  Q_DECLARE_PRIVATE(ICurve)
public:
  virtual ~ICurve();
  virtual void prepare() ;
  virtual void init() = 0;
  virtual void exec();

  virtual void calculate() = 0;

  virtual QString name() = 0;
  virtual QString note() = 0;

  virtual ICurve *clone() = 0;

  void setName(const QString &name);
  void setNote(const QString &note);
  virtual QString displayName();
  virtual QString fullName();

  void addConstInputByName(const QString &name);
  void addVarInputByName(const QString &name);
  void addUnit(const QString &uName,double k);

  void setUnit(const QString &uName);
  double curUnitK();
  QString curUnitName();
  QStringList unitNames();

  QStringList constInputKeys();
  QStringList varInputsKeys();
  void fillConstInputsPrm(int inx, const CurvePrm &prm);
  void fillVarInputsPrm(int inx ,const CurvePrm &prm);

  void setConstInputK(int channel,double value);
  QVector<double> &varInputVector(int channel);

  int rowInx() const;
  void setRowInx(int rowInx);

  int devInx() const;
  void setDevInx(int devInx);

  QString devName() const;
  void setDevName(const QString &devName);

  double samplInterval() const;
  void setSamplInterval(double samplInterval);

  void adjustData();

  void setStorePointCount(qint32 storePointCount);

protected:


};

Q_DECLARE_INTERFACE(ICurve,ICurve_iid)

#endif // ICURVE_H
