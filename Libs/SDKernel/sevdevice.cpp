#include "sevdevice.h"
#include "sevdeviceprivate_p.h"
#include "linksocket.h"
#include "sdtglobaldef.h"
#include "deviceconfig.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "sevdspmap.h"
#include "sevpwrboard.h"
#include "sevctrboard.h"

#include <QTreeWidget>
#include <QStringList>
#include <QDebug>
#include <QTreeWidgetItemIterator>


SevDevicePrivate::SevDevicePrivate(SevDevice *sev, QObject *parent):QObject(parent),q_ptr(sev),m_configTree(NULL)
{

}

SevDevicePrivate::~SevDevicePrivate()
{
  qDebug()<<"SevDevicePrivate destruct-->";
  if(m_configTree!=NULL)
  {
    delete m_configTree;
    m_configTree=NULL;
  }
  delete m_dspMap;
  delete m_pwrBoard;
  delete m_targetTree;
  delete m_ctrBoard;
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

void SevDevicePrivate::initConfig(const DeviceConfig *dConfig)
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
  m_rnStationId=dConfig->m_rnStationId;
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
    if(itemType->text(GT::COL_TARGET_CONFIG_NAME)==m_typeName)
      break;
  }
  Q_ASSERT(itemType!=NULL);
  for(int i=0;i<itemType->childCount();i++)
  {
    itemModel=itemType->child(i);
//    qDebug()<<itemModel->text(SYSCONFIG_COL_NAME)<<m_modeName;
    if(itemModel->text(GT::COL_TARGET_CONFIG_NAME)==m_modeName)
      break;
  }
  Q_ASSERT(itemModel!=NULL);
  for(int i=0;i<itemModel->childCount();i++)
  {
    itemVer=itemModel->child(i);
    if(itemVer->text(GT::COL_TARGET_CONFIG_NAME)==m_version)
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

void SevDevicePrivate::init(const DeviceConfig *dConfig)
{
  qDebug()<<"init Config";
  emit initProgressInfo(3,tr("init Config"));
  initConfig(dConfig);

  m_filePath=GTUtils::sysPath()+m_typeName+"/"+m_modeName+"/"+m_version+"/";

  qDebug()<<"findTargetTree";
  emit initProgressInfo(5,tr("findTargetTree"));
  findTargetTree();

  qDebug()<<"new SevDspMap";
  m_dspMap=new SevDspMap(this,0);
  connect(m_dspMap,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  m_dspMap->initTreeMap();

  qDebug()<<"new SevPwrBoard";
  m_pwrBoard=new SevPwrBoard(this,0);
  m_ctrBoard=new SevCtrBoard(this,0);
  m_socket=new LinkSocket(this,0);

}


SevDevice::SevDevice(QObject *parent):QObject(parent)
{

}
SevDevice::~SevDevice()
{
  qDebug()<<"SevDevice destruct-->";
  delete d_ptr;
}
bool SevDevice::init(const DeviceConfig *dConfig)
{
  emit initProgressInfo(2,tr("SevDevice init"));
  d_ptr=new SevDevicePrivate(this);
  connect(d_ptr,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  Q_D(SevDevice);
  d->init(dConfig);
  return true;
}

void SevDevice::adjustSocket(ComDriver::ICom *com)
{
  Q_D(SevDevice);
//  d->m_socket->connect();
}
bool SevDevice::enableConnection(void (*processCallBack)(void *argv, short *value), void *uiProcessBar)
{
  Q_D(SevDevice);
  return d->m_socket->connect(processCallBack,uiProcessBar);
}

void SevDevice::disableConnection()
{
  Q_D(SevDevice);
  d->m_socket->disConnect();
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
QTreeWidgetItem *SevDevice::targetTree() const
{
  Q_D(const SevDevice);
  return d->m_targetTree;
}

QTreeWidget *SevDevice::axisTreeSource(int axis,int page) const
{
  Q_D(const SevDevice);
  return d->m_dspMap->axisTreeWidget(axis,page);
}
QTreeWidget *SevDevice::globalTreeSource(int page) const
{
  Q_D(const SevDevice);
  return d->m_dspMap->globalTreeWidget(page);
}
void SevDevice::qmlTest()
{
  qDebug()<<"this is qml signals to device";
}

void SevDevice::onReadPageFlash(int axis,QTreeWidget *tree)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return;

  QTreeWidgetItemIterator it(tree);
  QTreeWidgetItem *item;

  while (*it)
  {
    item=(*it);
    qDebug()<<axis<<item->text(0);

    d->m_socket->readPageFlash(axis,item);

    it++;
  }
}
void SevDevice::onWritePageFlash(int axis,QTreeWidget *tree)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return;

  QTreeWidgetItemIterator it(tree);
  QTreeWidgetItem *item;

  while (*it)
  {
    item=(*it);

    d->m_socket->writePageFlash(axis,item);

    it++;
  }
}
