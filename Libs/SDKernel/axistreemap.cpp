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
  axisItem=targetTree->child(GT::ROW_TARGET_CONFIG_AXIS);

  QTreeWidget *tree;
  QTreeWidgetItem *item=NULL;
  QString file;

//  qDebug()<<"childCount"<<axisItem->childCount();

  //找到Axis节点下所有的项
  for(int i=0;i<axisItem->childCount();i++)
  {
    item=axisItem->child(i);
    Q_ASSERT(item!=NULL);

    file=filePath;
    qDebug()<<item->text(0)<<item->text(4)<<item->text(5);

    if((item->text(GT::COL_TARGET_CONFIG_FILESRCTYPE)=="1"))
    {
      file+="page/"+item->text(GT::COL_TARGET_CONFIG_XML)+QString::number(m_axis%2);
//      qDebug()<<file;
    }
    else
    {
      file+=item->text(GT::COL_TARGET_CONFIG_XML);
    }
    file+=".xml";
//    qDebug()<<file;

    tree=QtTreeManager::createTreeWidgetFromXmlFile(file);
    Q_ASSERT(tree);

    m_axisTreeList.append(tree);
  }
}

AxisTreeMap::~AxisTreeMap()
{
  qDebug()<<m_axis<<" AxisTreeMap-->destruct";
  GT::deepClearList(m_axisTreeList);
//  GT::deepClearList(m_globalTreeList);
}
