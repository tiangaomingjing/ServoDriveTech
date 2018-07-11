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
  QTreeWidget *axisTreeWidget(int axis,int page) const ;
  QTreeWidget *axisTreeWidget(int axis,const QString &name) const ;
  QTreeWidget *globalTreeWidget(int page) const ;

signals:

public slots:

protected:
  SevDevicePrivate *q_ptr;
  QList<AxisTreeMap*>m_axisTreeMapList;//每一个轴axis page tree
  QList<QTreeWidget *>m_globalTreeList;//整个设置公共的 page tree
  QTreeWidget *m_ramTree;
  QTreeWidget *m_flashTree;

};

#endif // IDSPMAP_H
