#ifndef AXISTREEMAP_H
#define AXISTREEMAP_H

#include <QObject>
class QTreeWidget;
class QTreeWidgetItem;
class AxisTreeMap : public QObject
{
  Q_OBJECT
public:
  enum{
    SYSCONFIG_COL_NAME,
    SYSCONFIG_COL_PRM,
    SYSCONFIG_COL_CLASSNAME,
    SYSCONFIG_COL_XMLNAME,
    SYSCONFIG_COL_INDEX,
    SYSCONFIG_COL_ISGLOBAL
  }SysConfigColumnInx;

  explicit AxisTreeMap(quint8 axis, const QTreeWidgetItem *targetTree, const QString &filePath, QObject *parent = 0);
  ~AxisTreeMap();


  QList<QTreeWidget *>m_axisTreeList;
  QList<QTreeWidget *>m_globalTreeList;
  quint8 m_axis;

signals:

public slots:


};

#endif // AXISTREEMAP_H
