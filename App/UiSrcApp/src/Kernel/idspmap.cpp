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

QTreeWidget *IDspMap::globalTreeWidget(int page) const
{
  return m_globalTreeList.at(page);
}
