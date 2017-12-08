#include "sevdspmap.h"
#include "sevdevice.h"
#include "sevdeviceprivate_p.h"
#include "axistreemap.h"
#include "qttreemanager.h"
#include "gtutils.h"
#include "sdtglobaldef.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>

SevDspMap::SevDspMap(SevDevicePrivate *sev, QObject *parent):IDspMap(sev,parent)
{

}
SevDspMap::~SevDspMap()
{
  qDebug()<<"SevDspMap destruct-->";
  GT::deepClearList(m_treeMapList);
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
  int inc=60/q_ptr->m_axisNum;
  int sum=5;
  for(int i=0;i<q_ptr->m_axisNum;i++)
  {
    sum+=inc;
    emit initProgressInfo(sum,tr("new AxisTreeMap %1").arg(i+1));
    GTUtils::delayms(10);
    treeMap=new AxisTreeMap(i,target,q_ptr->m_filePath);
    Q_ASSERT(treeMap!=NULL);
    m_treeMapList.append(treeMap);
  }

  qDebug()<<"build ram tree";
  file=q_ptr->m_filePath+RAM_ALL_PRM_NAME;
  m_ramTree=QtTreeManager::createTreeWidgetFromXmlFile(file);
  Q_ASSERT(m_ramTree!=NULL);

  file=q_ptr->m_filePath+FLASH_ALL_PRM_NAME;
  return true;
}
