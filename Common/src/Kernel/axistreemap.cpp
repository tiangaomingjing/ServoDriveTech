#include "axistreemap.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "sdtglobaldef.h"

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QDebug>

AxisTreeMap::AxisTreeMap(quint8 axis, const QTreeWidgetItem *targetTree, const QString &filePath, QObject *parent) :
  QObject(parent),
  m_axis(axis)
{
  QTreeWidgetItem *axisItem;
  axisItem=targetTree->child(0);

  QTreeWidgetItem *globalItem;
  globalItem=targetTree->child(1);

  QTreeWidget *tree;
  QTreeWidgetItem *item=NULL;
  QString file;

  qDebug()<<"childCount"<<axisItem->childCount();

  for(int i=0;i<axisItem->childCount();i++)
  {
    item=axisItem->child(i);
    Q_ASSERT(item!=NULL);

    file=filePath+item->text(SYSCONFIG_COL_XMLNAME);

    if((item->text(SYSCONFIG_COL_NAME)=="RAM")||(item->text(SYSCONFIG_COL_NAME)=="FLASH"))
    {
      file+=QString::number(m_axis%2);
      qDebug()<<file;
    }
    file+=".xml";

    tree=QtTreeManager::createTreeWidgetFromXmlFile(file);
    Q_ASSERT(tree);
  }
  m_axisTreeList.append(tree);

//  QList<QTreeWidget *>m_globalTreeList;
}

AxisTreeMap::~AxisTreeMap()
{
  GT::deepClearList(m_axisTreeList);
  GT::deepClearList(m_globalTreeList);
  qDebug()<<m_axis<<" AxisTreeMap-->destruct";
}
