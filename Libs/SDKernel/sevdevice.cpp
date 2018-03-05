﻿#include "sevdevice.h"
#include "sevdeviceprivate_p.h"
#include "linksocket.h"
#include "sdtglobaldef.h"
#include "deviceconfig.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "sevdspmap.h"
#include "sevctrboard.h"
#include "verattribute.h"
#include "Option"
#include "generalcmd.h"

#include <QTreeWidget>
#include <QStringList>
#include <QDebug>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>


SevDevicePrivate::SevDevicePrivate(SevDevice *sev, QObject *parent):QObject(parent),
  q_ptr(sev),
  m_configTree(NULL),
  m_targetTree(NULL),
  m_dspMap(NULL),
  m_pwrBoard(NULL),
  m_ctrBoard(NULL),
  m_verAttribute(NULL),
  m_devConfig(new DeviceConfig),
  m_connected(false),
  m_genCmd(NULL)
{

}

SevDevicePrivate::~SevDevicePrivate()
{
  qDebug()<<"SevDevicePrivate destruct-->";
  GT::deletePtrObject(m_configTree);
  GT::deletePtrObject(m_targetTree);
  GT::deletePtrObject(m_dspMap);
  GT::deletePtrObject(m_pwrBoard);
  GT::deletePtrObject(m_ctrBoard);
  GT::deletePtrObject(m_devConfig);
  GT::deletePtrObject(m_verAttribute);
  GT::deletePtrObject(m_genCmd);
}
QTreeWidget *SevDevicePrivate::configTree()
{
  m_configTree->clear();

  return m_configTree;
}

void SevDevicePrivate::initConfig(const DeviceConfig *dConfig)
{
    qDebug()<<"initial private";
  m_devConfig->m_devId=dConfig->m_devId;
  m_devConfig->m_comType=dConfig->m_comType;
  m_devConfig->m_axisNum=dConfig->m_axisNum;
  m_devConfig->m_typeName=dConfig->m_typeName;
  m_devConfig->m_modeName=dConfig->m_modeName;
  m_devConfig->m_version=dConfig->m_version;
  m_devConfig->m_pwrId=dConfig->m_pwrId;
  m_devConfig->m_ctrId=dConfig->m_ctrId;
  m_devConfig->m_fpgaId=dConfig->m_fpgaId;
  m_devConfig->m_rnStationId=dConfig->m_rnStationId;
}

QTreeWidgetItem* SevDevicePrivate::findTargetTree()
{
  QString comIndexFile=GTUtils::sysPath()+"SysMap/"+COMINDEX_NAME;
  QTreeWidget *comInxTree=QtTreeManager::createTreeWidgetFromXmlFile(comIndexFile);
  if (comInxTree == NULL)
  {
    qDebug()<<"can not create comInxTree...........";
    return NULL;
  }
  QString comName="RnNet";
  quint8 comId=m_devConfig->m_comType;
//  qDebug()<<"comId ="<<comId;
  for(int i=0;i<comInxTree->invisibleRootItem()->childCount();i++)
  {
    quint8 id=comInxTree->topLevelItem(i)->text(0).toUInt();
    qDebug()<<"id "<<id;
    if(id==comId)
    { 
      comName=comInxTree->topLevelItem(i)->text(1);
//      qDebug()<<"find id ="<<id<<"comname"<<comName;
      break;
    }
  }
  QString targetTreePath=GTUtils::sysPath()+"SysMap/"+comName+"/"+\
      m_devConfig->m_typeName+"/"+\
      m_devConfig->m_modeName+"/"+\
      m_devConfig->m_version+"/"+TARGET_CONFIG_TREE_NAME;

//  qDebug()<<"targetTreePath :"<<targetTreePath;

  QTreeWidget *targetTree=QtTreeManager::createTreeWidgetFromXmlFile(targetTreePath);
  if(targetTree==NULL)
  {
    delete comInxTree;
    return NULL;
  }
  m_targetTree=targetTree->topLevelItem(0)->clone();

  delete comInxTree;
  delete targetTree;
  return m_targetTree;
}

bool SevDevicePrivate::init(const DeviceConfig *dConfig)
{
  qDebug()<<"init Config";
  emit initProgressInfo(3,tr("init Config"));
  initConfig(dConfig);

  m_filePath=GTUtils::sysPath()+m_devConfig->m_typeName+"/"+m_devConfig->m_modeName+"/"+m_devConfig->m_version+"/";

  qDebug()<<"findTargetTree";
  emit initProgressInfo(5,tr("findTargetTree"));
  QTreeWidgetItem *target=findTargetTree();
  if(target==NULL)
    return false;

  qDebug()<<"new SevDspMap";
  emit initProgressInfo(3,tr("New SevDspMap"));
  m_dspMap=new SevDspMap(this,0);
  connect(m_dspMap,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  m_dspMap->initTreeMap();

  qDebug()<<"new SevPwrBoard";
  emit initProgressInfo(3,tr("New SevPwrBoard"));
  m_pwrBoard=new SevPwrBoard(this,0);
  m_ctrBoard=new SevCtrBoard(this,0);
  m_socket=new LinkSocket(this,0);
  m_verAttribute=new VerAttribute(0);

  //通用指令
  emit initProgressInfo(3,tr("New GeneralCmd"));
  m_genCmd=new GeneralCmd(m_socket->comObject());
  QString gcmdPath=m_filePath+"cmd/GeneralCmd.xml";
  QTreeWidget *cmdTree=QtTreeManager::createTreeWidgetFromXmlFile(gcmdPath);
  m_genCmd->fillCmdMaps(cmdTree);
  delete cmdTree;

  return true;
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
  d_ptr=new SevDevicePrivate(this,0);
  connect(d_ptr,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  Q_D(SevDevice);
  return d->init(dConfig);
}

void SevDevice::adjustSocket(ComDriver::ICom *com)
{
  Q_D(SevDevice);
//  d->m_socket->connect();
}
ComDriver::ICom *SevDevice::socketCom() const
{
  Q_D(const SevDevice);
  return d->m_socket->comObject();
}
bool SevDevice::enableConnection(void (*processCallBack)(void *argv, short *value), void *uiProcessBar)
{
  Q_D(SevDevice);
  d->m_connected=d->m_socket->connect(processCallBack,uiProcessBar);
  return d->m_connected;
}

void SevDevice::disableConnection()
{
  Q_D(SevDevice);
  d->m_connected=false;
  d->m_socket->disConnect();
}
bool SevDevice::isConnecting() const
{
  Q_D(const SevDevice);
  return d->m_connected;
}

quint64 SevDevice::genCmdRead(const QString &cmdReadName,qint16 axisIndex,bool &isOk)
{
  Q_D(SevDevice);
  return d->m_genCmd->read(cmdReadName,axisIndex,isOk);
}

bool SevDevice::genCmdWrite(const QString &cmdWriteName,quint64 value,qint16 axisIndex)
{
  Q_D(SevDevice);
  return d->m_genCmd->write(cmdWriteName,value,axisIndex);
}

QString SevDevice::typeName() const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_typeName;
}
QString SevDevice::modelName() const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_modeName;
}
QString SevDevice::versionName()const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_version;
}
quint32 SevDevice::devId() const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_devId;
}
quint32 SevDevice::pwrId() const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_pwrId;
}
quint32 SevDevice::ctrId() const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_ctrId;
}
quint32 SevDevice::fpgaId() const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_fpgaId;
}
quint8 SevDevice::axisNum() const
{
  Q_D(const SevDevice);
  return d->m_devConfig->m_axisNum;
}
DeviceConfig *SevDevice::deviceConfig() const
{
  Q_D(const SevDevice);
  return d->m_devConfig;
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
void SevDevice::setVersionAttributeActive()
{
  Q_D(SevDevice);
  d->m_verAttribute->setActive(this);
}

void SevDevice::qmlTest()
{
  qDebug()<<"this is qml signals to device";
}

bool SevDevice::onReadPageFlash(int axis,QTreeWidget *tree)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;

  QTreeWidgetItemIterator it(tree);
  QTreeWidgetItem *item;
  bool rOk=true;
  while (*it)
  {
    item=(*it);
    rOk=d->m_socket->readPageFlash(axis,item);
    if(!rOk)
    {
      rOk=false;
      break;
    }
    it++;
  }
  return rOk;
}
bool SevDevice::onWritePageFlash(int axis,QTreeWidget *tree)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;

  bool checkOk=true;
  checkOk=checkParameters(axis,tree);
  if(!checkOk)
    return false;


  QTreeWidgetItemIterator it(tree);
  QTreeWidgetItem *item;
  bool writeOk=true;
  while (*it)
  {
    item=(*it);
    qDebug()<<"write item"<<item->text(GT::COL_PAGE_TREE_NAME)<<"value"<<item->text(GT::COL_PAGE_TREE_VALUE);

    writeOk=d->m_socket->writePageFlash(axis,item);
    qDebug()<<"writeOk"<<writeOk;
    if(writeOk)
    {
      d->m_socket->readPageFlash(axis,item);
      emit itemRangeValid(item,(int)OptFace::EDIT_TEXT_STATUS_DEFAULT);
    }
    else
    {
      QMessageBox::warning(0,tr("Write Error"),tr("Write Flash Parameter Error:%1 ").arg(item->text(GT::COL_PAGE_TREE_NAME)));
      break;
    }

    it++;
  }
  return writeOk;
}

bool SevDevice::checkPropertyParameters(QTreeWidgetItem *item)
{
  bool checked=true;
  double value ,min,max;
  value=item->text(GT::COL_PAGE_TREE_VALUE).toDouble();
  min=item->text(GT::COL_PAGE_TREE_DLIMIT).toDouble();
  max=item->text(GT::COL_PAGE_TREE_ULIMIT).toDouble();
  if(((value>=min)&&(value<=max))==false)
  {
    checked=false;
    emit itemRangeValid(item,(int)OptFace::EDIT_TEXT_STATUS_ERROR);
    double scale;
    bool ok=true;
    scale=item->text(GT::COL_PAGE_TREE_SCALE).toDouble(&ok);
    if(!ok&&scale==0)
      scale=1;
    value=value/scale;
    min=min/scale;
    max=max/scale;
    qDebug()<<"value"<<value<<"min"<<min<<"max"<<max;
    QString msg=QString(tr("CheckPrm Error:%1 %2 is out of range %3 -- %4\n")\
                             .arg(item->text(GT::COL_PAGE_TREE_NAME))\
                             .arg(value)\
                             .arg(min)\
                             .arg(max));
    QMessageBox::warning(0,tr("Prm Error"),msg);
  }
  return checked;
}
bool SevDevice::checkPowerBoardParameters(QTreeWidgetItem *item, const QMap<QString, PowerBoardLimit> *limit)
{
  QString name=item->text(GT::COL_PAGE_TREE_NAME);
  bool checked=true;

  if(limit->contains(name))
  {
    double min,max,value=0;
    value=item->text(GT::COL_PAGE_TREE_VALUE).toDouble();
    min=limit->value(name).min;
    max=limit->value(name).max;
    if(!(value>=min&&value<=max))
    {
      checked=false;
      emit itemRangeValid(item,(int)OptFace::EDIT_TEXT_STATUS_ERROR);
      QMessageBox::warning(0,tr("Prm Error"),tr("PowerBoard CheckPrm Error:%1 is out of range").arg(name));
    }
  }
  return checked;
}

bool SevDevice::checkParameters(int axis,QTreeWidget *tree)
{

  QTreeWidgetItem *item=NULL;
  bool isOk=true;

  for(int i=0;i<tree->topLevelItemCount();i++)
  {
    //1 检查输入值是否在约束范围内
    item=tree->topLevelItem(i);
    isOk=checkPropertyParameters(item);
    qDebug()<<"TEST_OUT"<<"checkPropertyParameters(item) ok="<<isOk;
    if(!isOk)
      break;
  }
  if(isOk)
  {
    //2 检查输入值是否在powerboard的约束
    Q_D(SevDevice);
    QMap<QString ,PowerBoardLimit> limit;
    if(!(d->m_pwrBoard->pwrLimitMapList()->isEmpty()))
    {
      limit=d->m_pwrBoard->pwrLimitMapList()->at(axis);

      for(int i=0;i<tree->topLevelItemCount();i++)
      {
        item=tree->topLevelItem(i);
        isOk=checkPowerBoardParameters(item,&limit);
        if(!isOk)
          break;
      }
    }
  }

  return isOk;
}
