#ifndef ICURVE_H
#define ICURVE_H

#include "icurve_global.h"
#include <QObject>
#include <QVector>
#include <QHash>
#include <QColor>
#include <QList>

#define SAMPLING_INTERVAL_US 62.5

#define ICurve_iid "gt.plot.curve.icurve"
class CurveData
{
public:
  CurveData(){}
  QVector<double>values;
  QVector<double>keys;
};

class CurvePrm
{
public:
  CurvePrm(){}
  quint16 bytes;
  quint16 offtAddr;
  quint16 baseAddr;
};

class CurveConst
{
public:
  QString keyName;
  CurvePrm prm;
  double constK;
};
class CurveVar
{
public:
  QString keyName;
  CurvePrm prm;
  QVector<double>datas;
};
class QTreeWidgetItem;
class ICURVESHARED_EXPORT ICurve
{
public:
  virtual ~ICurve();
  virtual void prepare() ;
  virtual void init() = 0;
  virtual void exec();



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
  void setVarInputVector(int channel ,const QVector<double> &in);

  int rowInx() const;
  void setRowInx(int rowInx);

  int devInx() const;
  void setDevInx(int devInx);

  QString devName() const;

  double samplInterval() const;
  void setSamplInterval(int samplIntervalScale);

  void adjustData();

  void setStorePointCount(qint32 storePointCount);

  int axisInx() const;
  void setAxisInx(int axisInx);

  QColor color() const;
  void setColor(const QColor &color);

  bool isDraw() const;
  void setIsDraw(bool isDraw);

  QList<CurveVar> varInputs() const;

  QList<CurveConst> constInputs() const;

  int dspInx() const;
  void setDspInx(int dspInx);

  CurveData *cData();
  CurveData *sData() ;

protected:
  virtual void calculate() = 0;

protected:

  class ICurvePrivate
  {
  public:
    ICurvePrivate();

    int m_rowInx;
    int m_axisInx;
    int m_dspInx;
    int m_devInx;

    bool m_isDraw;
    QColor m_color;
    QString m_name;
    QString m_note;
    QString m_unitName;

    double m_k;
    double m_samplInterval;//s
    double m_currentTime;//s
    qint32 m_storePointCount;

    QList<CurveConst>m_constInputs;
    QList<CurveVar>m_varInputs;
    QHash<QString,double> m_units;

    CurveData m_cData;
    CurveData m_sData;

    QString m_pluginName;
  };

  ICurvePrivate dd;

};

Q_DECLARE_INTERFACE(ICurve,ICurve_iid)

#endif // ICURVE_H
