#ifndef IDSPMAP_H
#define IDSPMAP_H

#include <QObject>

class AxisTreeMap;
class SevDevice;
class QTreeWidget;

class IDspMap : public QObject
{
  Q_OBJECT
public:
  explicit IDspMap(SevDevice *sev,QObject *parent=0):QObject(parent),q_ptr(sev){}
  virtual ~IDspMap(){}
  virtual bool initTreeMap()=0;

signals:

public slots:

protected:
  SevDevice *q_ptr;
  QList<AxisTreeMap*>m_treeMapList;
  QTreeWidget *m_ramTree;
  QTreeWidget *m_flashTree;

};

#endif // IDSPMAP_H
