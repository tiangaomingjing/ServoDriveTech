#ifndef AXISTREEMAP_H
#define AXISTREEMAP_H

#include <QObject>
class QTreeWidget;
class AxisTreeMap : public QObject
{
  Q_OBJECT
public:
  explicit AxisTreeMap(QObject *parent = 0);
  ~AxisTreeMap(){}

  QList<QTreeWidget *>m_axisTreeList;
  QList<QTreeWidget *>m_globalTreeList;

signals:

public slots:


};

#endif // AXISTREEMAP_H
