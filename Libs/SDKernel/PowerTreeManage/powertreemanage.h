#ifndef POWERTREEMANAGE_H
#define POWERTREEMANAGE_H

#include <QObject>
#include <QVector>


class QTreeWidgetItem;
class QTreeWidget;
class DeviceConfig;

struct PowerBoardLimit{
  double max;
  double min;
};
struct SamplingData{
  quint8 m_type;
  double m_value;
};

typedef QList<SamplingData> SamplingDataList;

//class SamplingDataInfo{
//public:
//  SamplingDataInfo();
//  ~SamplingDataInfo();

//  QVector<double> values() const;
//  void setValues(const QVector<double> &values);

//  QVector<quint8> types() const;
//  void setTypes(const QVector<quint8> &types);

//  QStringList mathExp() const;
//  void setMathExp(const QStringList &mathExp);

//private:
//  QVector<quint8> m_types;//储存每一个轴对应的采样类型
//  QVector<double>m_values;//储存每一个轴对应类型下的采样值
//  QList<SamplingData> m_data;
//  QStringList m_mathExp;
//};

class PowerTreeManage : public QObject
{
  Q_OBJECT
public:

  //explicit PowerTreeManage(QTreeWidget *powerTree,QObject *parent = 0);
  explicit PowerTreeManage(DeviceConfig *config, QObject *parent = 0);
  ~PowerTreeManage();
  bool updatePowerLimitMapList(QList<QMap<QString ,PowerBoardLimit>>&powerLimitMapList);
  SamplingDataList samplingDataList(bool *isOK);
signals:

public slots:
private:
  //QTreeWidgetItem *findTargetBoard(const quint32 id);
  void insertLimit(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
  void insertLimitRecursion(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
  QTreeWidgetItem *findUniqueItemByName(QTreeWidgetItem *item,QString &targetName);
  QTreeWidgetItem *findUniqueItemByNameRecursion(QTreeWidgetItem *item,QString &targetName);
  QTreeWidgetItem * detailInfoTreeItem(QTreeWidgetItem *target);
  QTreeWidgetItem * basicInfoTreeItem(QTreeWidgetItem *target);
  QString getPath(QTreeWidgetItem *item);
  QString getFilterPath(QTreeWidgetItem *item);
private:
  QTreeWidget *m_powerTree;
  QTreeWidgetItem *mp_pwrTarget;
  QString m_filterPath;
  QStringList m_filterList;
  DeviceConfig *m_sevConfig;
};

#endif // POWERTREEMANAGE_H
