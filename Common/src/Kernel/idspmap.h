#ifndef IDSPMAP_H
#define IDSPMAP_H

#include <QObject>

class AxisTreeMap;
class SevDevicePrivate;
class QTreeWidget;

class IDspMap : public QObject
{
  Q_OBJECT
public:
  explicit IDspMap(SevDevicePrivate *sev,QObject *parent=0);
  virtual ~IDspMap();
  virtual bool initTreeMap()=0;

signals:

public slots:

protected:
  SevDevicePrivate *q_ptr;
  QList<AxisTreeMap*>m_treeMapList;
  QTreeWidget *m_ramTree;
  QTreeWidget *m_flashTree;

};

#endif // IDSPMAP_H
