#include "sevdevice.h"
#include "sevdeviceprivate_p.h"
#include "linksocket.h"
#include "sdtglobaldef.h"
#include "deviceconfig.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "sevdspmap.h"

#include <QTreeWidget>
#include <QStringList>
#include <QDebug>


SevDevicePrivate::SevDevicePrivate(SevDevice *sev):q_ptr(sev)
{

}

SevDevicePrivate::~SevDevicePrivate()
{
  delete m_configTree;
  delete m_dspMap;
}
QTreeWidget *SevDevicePrivate::configTree()
{
  m_configTree->clear();
  QStringList list;
  list<<"name"<<"parameter";
  m_configTree->setHeaderLabels(list);
  QTreeWidgetItem *item=new QTreeWidgetItem(m_configTree->invisibleRootItem());
  item->setText(0,"Device");
  QTreeWidgetItem *itemCom=new QTreeWidgetItem(item);
  itemCom->setText(0,m_socket->socketName());
  itemCom->setText(1,QString::number(m_socket->socketTypeId()));
  QTreeWidgetItem *itemType=new QTreeWidgetItem(itemCom);
  itemType->setText(0,m_typeName);
  itemType->setText(1,QString::number(m_axisNum));
  QTreeWidgetItem *itemModel=new QTreeWidgetItem(itemType);
  itemModel->setText(0,m_modeName);
  itemModel->setText(1,"NULL");
  QTreeWidgetItem *itemVer=new QTreeWidgetItem(itemModel);
  itemVer->setText(0,m_version);
  itemVer->setText(1,"NULL");
  return m_configTree;
}

void SevDevicePrivate::init(const DeviceConfig *dConfig)
{
  m_devId=dConfig->m_devId;
  m_comType=dConfig->m_comType;
  m_axisNum=dConfig->m_axisNum;
  m_typeName=dConfig->m_typeName;
  m_modeName=dConfig->m_modeName;
  m_version=dConfig->m_version;
  m_pwrId=dConfig->m_pwrId;
  m_ctrId=dConfig->m_ctrId;
  m_fpgaId=dConfig->m_fpgaId;

  m_filePath=GTUtils::sysPath()+m_typeName+"/"+m_modeName+"/"+m_version+"/";

  findTargetTree();

  m_dspMap=new SevDspMap(this);

}

QTreeWidgetItem* SevDevicePrivate::findTargetTree()
{
  QString sysFile=GTUtils::sysPath()+SYSCONFIGTREE_NAME;
  QTreeWidget *allTree=QtTreeManager::createTreeWidgetFromXmlFile(sysFile);
  Q_ASSERT(allTree!=NULL);
  QTreeWidgetItem *item=allTree->topLevelItem(0)->child(m_comType);
  QTreeWidgetItem *itemType=NULL;
  QTreeWidgetItem *itemModel=NULL;
  QTreeWidgetItem *itemVer=NULL;
  for(int i=0;i<item->childCount();i++)
  {
    itemType=item->child(i);
//    qDebug()<<itemType->text(SYSCONFIG_COL_NAME)<<i;
    if(itemType->text(SYSCONFIG_COL_NAME)==m_typeName)
      break;
  }
  Q_ASSERT(itemType!=NULL);
  for(int i=0;i<itemType->childCount();i++)
  {
    itemModel=itemType->child(i);
//    qDebug()<<itemModel->text(SYSCONFIG_COL_NAME)<<m_modeName;
    if(itemModel->text(SYSCONFIG_COL_NAME)==m_modeName)
      break;
  }
  Q_ASSERT(itemModel!=NULL);
  for(int i=0;i<itemModel->childCount();i++)
  {
    itemVer=itemModel->child(i);
    if(itemVer->text(SYSCONFIG_COL_NAME)==m_version)
      break;
  }
  Q_ASSERT(itemVer!=NULL);
  m_targetTree=itemVer->clone();
//  QTreeWidget *w=new QTreeWidget;
//  w->addTopLevelItem(m_targetTree);
//  w->show();
  allTree->clear();
  delete allTree;
  return m_targetTree;
}




SevDevice::SevDevice(const DeviceConfig *dConfig, QObject *parent):QObject(parent),d_ptr(new SevDevicePrivate(this))
{
  Q_D(SevDevice);
  d->init(dConfig);
}
void SevDevice::adjustSocket(ComDriver::ICom *com)
{
  Q_D(SevDevice);
  d->m_socket->connect(com);
}

QString SevDevice::typeName() const
{
  Q_D(const SevDevice);
  return d->m_typeName;
}
QString SevDevice::modelName() const
{
  Q_D(const SevDevice);
  return d->m_modeName;
}
QString SevDevice::versionName()const
{
  Q_D(const SevDevice);
  return d->m_version;
}

quint32 SevDevice::pwrId() const
{
  Q_D(const SevDevice);
  return d->m_pwrId;
}
quint32 SevDevice::ctrId() const
{
  Q_D(const SevDevice);
  return d->m_ctrId;
}
quint32 SevDevice::fpgaId() const
{
  Q_D(const SevDevice);
  return d->m_fpgaId;
}
quint8 SevDevice::axisNum() const
{
  Q_D(const SevDevice);
  return d->m_axisNum;
}
