#include "idspmap.h"
#include "axistreemap.h"

IDspMap::IDspMap(SevDevicePrivate *sev, QObject *parent):QObject(parent),q_ptr(sev),m_ramTree(NULL),m_flashTree(NULL)
{

}

IDspMap::~IDspMap()
{

}

QTreeWidget *IDspMap::axisTreeWidget(int axis,int page) const
{
  return m_axisTreeMapList.at(axis)->m_axisTreeList.at(page);
}

QTreeWidget *IDspMap::axisTreeWidget(int axis, const QString &name) const
{
  QTreeWidget *tree=NULL;
  if(m_axisTreeMapList.at(axis)->m_nameTrees.contains(name))
    tree = m_axisTreeMapList.at(axis)->m_nameTrees.value(name);
  return tree;
}

QTreeWidget *IDspMap::globalTreeWidget(int page) const
{
  if(page<m_globalTreeList.count())
    return m_globalTreeList.at(page);
  else
    return NULL;
}
