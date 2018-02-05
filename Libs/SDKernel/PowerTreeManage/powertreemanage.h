#ifndef POWERTREEMANAGE_H
#define POWERTREEMANAGE_H

#include <QObject>
#include <QVector>


class QTreeWidgetItem;
class QTreeWidget;

struct PowerBoardLimit{
  double max;
  double min;
};
class SamplingDataInfo{
public:
  SamplingDataInfo();
  ~SamplingDataInfo();

  QVector<double> values() const;
  void setValues(const QVector<double> &values);

  QVector<quint8> types() const;
  void setTypes(const QVector<quint8> &types);

  QStringList mathExp() const;
  void setMathExp(const QStringList &mathExp);

private:
  QVector<quint8> m_types;//储存每一个轴对应的采样类型
  QVector<double>m_values;//储存每一个轴对应类型下的采样值
  QStringList m_mathExp;
};

class PowerTreeManage : public QObject
{
  Q_OBJECT
public:

  //explicit PowerTreeManage(QTreeWidget *powerTree,QObject *parent = 0);
  explicit PowerTreeManage(const quint32 id,QObject *parent = 0);

  bool updatePowerLimitMapList(const QString &version, QList<QMap<QString ,PowerBoardLimit>>&powerLimitMapList);
  SamplingDataInfo samplingDataInfo(bool *isOK);
signals:

public slots:
private:
  //QTreeWidgetItem *findTargetBoard(const quint32 id);
  void insertLimit(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
  void insertLimitRecursion(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap);
  QTreeWidgetItem *findItemByName(QTreeWidgetItem *item,QString &targetName);
  QTreeWidgetItem *findItemByNameRecursion(QTreeWidgetItem *item,QString &targetName);
  QTreeWidgetItem * detailInfoTreeItem(QTreeWidgetItem *target);
  QTreeWidgetItem * basicInfoTreeItem(QTreeWidgetItem *target);
private:
  QTreeWidget *m_powerTree;
  QTreeWidgetItem *m_pwrTarget;
  QString m_filterPath;
  QStringList m_filterList;

};

#endif // POWERTREEMANAGE_H
