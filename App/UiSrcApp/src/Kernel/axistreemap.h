﻿#ifndef AXISTREEMAP_H
#define AXISTREEMAP_H

#include <QObject>
class QTreeWidget;
class QTreeWidgetItem;
class AxisTreeMap : public QObject
{
  Q_OBJECT
public:
  explicit AxisTreeMap(quint8 axis, const QTreeWidgetItem *targetTree, const QString &filePath, QObject *parent = 0);
  ~AxisTreeMap();


  QList<QTreeWidget *>m_axisTreeList;
  quint8 m_axis;

signals:

public slots:


};

#endif // AXISTREEMAP_H
