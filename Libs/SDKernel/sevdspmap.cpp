#include "sevdspmap.h"
#include "sevdevice.h"
#include "sevdeviceprivate_p.h"
#include "axistreemap.h"
#include "qttreemanager.h"
#include "gtutils.h"
#include "sdtglobaldef.h"
#include "deviceconfig.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>

SevDspMap::SevDspMap(SevDevicePrivate *sev, QObject *parent):IDspMap(sev,parent)
{

}
SevDspMap::~SevDspMap()
{
  qDebug()<<"SevDspMap destruct-->";
  GT::deepClearList(m_axisTreeMapList);
  GT::deepClearList(m_globalTreeList);
  delete m_ramTree;
}

bool SevDspMap::initTreeMap()
{
  QTreeWidgetItem *target=q_ptr->m_targetTree;
//    QTreeWidget *w=new QTreeWidget;
//    w->addTopLevelItem(target);
//    w->show();

  AxisTreeMap *treeMap=NULL;
  QString file;
  qDebug()<<"new AxisTreeMap";

  int inc=60/q_ptr->m_devConfig->m_axisNum;
  int sum=5;
  //建立每一个轴的数据
  for(int i=0;i<q_ptr->m_devConfig->m_axisNum;i++)
  {
    sum+=inc;
    emit initProgressInfo(sum,tr("New AxisTreeMap %1").arg(i+1));
    GTUtils::delayms(10);
    treeMap=new AxisTreeMap(i,target,q_ptr->m_filePath);
    Q_ASSERT(treeMap!=NULL);
    m_axisTreeMapList.append(treeMap);
  }

  //建立global节点下的数据
  QTreeWidgetItem *item;
  QTreeWidget *tree;
  for(int i=0;i<target->child(GT::ROW_TARGET_CONFIG_GLOBAL)->childCount();i++)
  {
    item=target->child(GT::ROW_TARGET_CONFIG_GLOBAL)->child(i);
    file=q_ptr->m_filePath+item->text(GT::COL_TARGET_CONFIG_XML)+".xml";

    tree=QtTreeManager::createTreeWidgetFromXmlFile(file);
    Q_ASSERT(tree);
    m_globalTreeList.append(tree);
  }
  /*
  qDebug()<<"build ram tree";
  file=q_ptr->m_filePath+RAM_ALL_PRM_NAME;
  m_ramTree=QtTreeManager::createTreeWidgetFromXmlFile(file);
  Q_ASSERT(m_ramTree!=NULL);

  file=q_ptr->m_filePath+FLASH_ALL_PRM_NAME;
  */
  return true;
}
