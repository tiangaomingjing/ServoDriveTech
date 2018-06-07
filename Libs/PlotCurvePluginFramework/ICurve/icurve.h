#ifndef ICURVE_H
#define ICURVE_H

#include "icurve_global.h"
#include "icurvedef.h"
#include <QObject>
#include <QVector>
#include <QHash>
#include <QColor>
#include <QList>

#define SAMPLING_INTERVAL_US 62.5

#define ICurve_iid "gt.plot.curve.icurve"

class QTreeWidgetItem;
class ICURVESHARED_EXPORT ICurve
{
public:
  typedef enum{
    COL_CURVE_XML_NAME ,
    COL_CURVE_XML_VALUE,
    COL_CURVE_XML_SIZE
  }CurveXmlColumn;

  virtual ~ICurve();
  virtual void prepare() ;
  virtual void init() = 0;
  virtual void exec();



  virtual QString name() = 0;
  virtual QString note() = 0;

  virtual ICurve *clone() = 0;
  virtual QString pluginName() = 0;

  virtual void reset() = 0;

  void setName(const QString &name);
  void setNote(const QString &note);
  virtual QString displayName();
  virtual QString fullName();

  virtual void write(QTreeWidgetItem *treeItem);
  virtual bool read(QTreeWidgetItem *treeItem);

//  virtual void write(ISave *save) {save->exec(this);}

  void addConstInputByName(const QString &name);
  void addVarInputByName(const QString &name);

  //单位处理
  void addUnit(const QString &uName,double k);
  void setUnit(const QString &uName);
  double unitValue(const QString &uName);
  double curUnitK();
  QString curUnitName();
  QStringList unitNames();

  QStringList constInputKeys();
  QStringList varInputsKeys();
  void fillConstInputsPrm(int inx, const CurvePrm &prm);
  void fillVarInputsPrm(int inx ,const CurvePrm &prm);

  void setConstInputK(int channel,double value);
  void setVarInputVector(int channel ,const QVector<double> &in);

  int devInx() const;
  void setDevInx(int devInx);

  QString devName() const;

  double samplInterval() const;
  void setSamplInterval(int samplIntervalScale);

  void setStorePointCount(quint32 storePointCount);

  int axisInx() const;
  void setAxisInx(int axisInx);

  QColor color() const;
  void setColor(const QColor &color);

  bool isDraw() const;
  void setIsDraw(bool isDraw);

  QList<CurveVar> & varInputs();

  QList<CurveConst> & constInputs();

  int dspInx() const;
  void setDspInx(int dspInx);

  void setAxisCount (int axisCount);
  int axisCount() const;

  CurveData *cData();
  CurveData *sData() ;

  void savePrepare();


//  void setPluginName(const QString &name);

protected:
  virtual void calculate() = 0;
  void adjustData();
  void updateCurrentTime();

protected:

  class ICurvePrivate
  {
  public:
    ICurvePrivate();

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
    quint32 m_storePointCount;

    QList<CurveConst>m_constInputs;
    QList<CurveVar>m_varInputs;

    QHash<QString,double> m_unitsHash;
    QStringList m_unitNameList;

    CurveData m_cData;
    CurveData m_sData;

    QString m_pluginName;
    int m_axisCount;
  };

  ICurvePrivate dd;

};

Q_DECLARE_INTERFACE(ICurve,ICurve_iid)

#endif // ICURVE_H
