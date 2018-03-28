#include "sevdevice.h"
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

#include <QTreeWidget>
#include <QStringList>
#include <QDebug>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>

#define CMD_PRO_ALM_FLAG "gSevDrv.sev_obj.cur.pro.alm_flag"

#define TEST_CHECKSTATUS 0

SevDevicePrivate::SevDevicePrivate(SevDevice *sev, QObject *parent):QObject(parent),
  q_ptr(sev),
  m_configTree(NULL),
  m_targetTree(NULL),
  m_dspMap(NULL),
  m_pwrBoard(NULL),
  m_ctrBoard(NULL),
  m_verAttribute(NULL),
  m_devConfig(new DeviceConfig),
  m_connected(false)
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
  emit initProgressInfo(3,tr("init Config"));
  initConfig(dConfig);

  m_filePath=GTUtils::sysPath()+m_devConfig->m_typeName+"/"+m_devConfig->m_modeName+"/"+m_devConfig->m_version+"/";

  emit initProgressInfo(5,tr("findTargetTree"));
  QTreeWidgetItem *target=findTargetTree();
  if(target==NULL)
    return false;

  emit initProgressInfo(10,tr("New SevDspMap"));
  m_dspMap=new SevDspMap(this,0);
  connect(m_dspMap,SIGNAL(initProgressInfo(int,QString)),this,SIGNAL(initProgressInfo(int,QString)));
  m_dspMap->initTreeMap();

  emit initProgressInfo(65,tr("New SevPwrBoard"));
  m_pwrBoard=new SevPwrBoard(this,0);
  m_ctrBoard=new SevCtrBoard(this,0);
  m_socket=new LinkSocket(this,0);
  m_verAttribute=new VerAttribute(0);

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

bool SevDevice::adjustSocket(void (*processCallBack)(void *argv, short *value), void *uiProcessBar)
{
  Q_D(SevDevice);
  qDebug()<<"adjustSocket isConnecting="<<isConnecting();
  if(isConnecting())
  {
    return true;
  }
  else
  {
    qDebug()<<"socket start adjust.....";
    return d->m_socket->adjust(processCallBack,uiProcessBar);
  }
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

bool SevDevice::containsCmd(const QString &cmdKey)
{
  Q_D(SevDevice);
  return d->m_socket->containsCmd(cmdKey);
}

quint64 SevDevice::genCmdRead(const QString &cmdReadName,qint16 axisIndex,bool &isOk)
{
  Q_D(SevDevice);
  return d->m_socket->genCmdRead(cmdReadName,axisIndex,isOk);
}

bool SevDevice::genCmdWrite(const QString &cmdWriteName,quint64 value,qint16 axisIndex)
{
  Q_D(SevDevice);
  return d->m_socket->genCmdWrite(cmdWriteName,value,axisIndex);
}

bool SevDevice::readGenItemRAM(quint16 axisInx, QTreeWidgetItem *item)
{
  Q_D(SevDevice);
  QString type;
  bool rOk=true;
  quint64 rv=0;

  type=item->text(COL_PAGE_TREE_TYPE);
  //通用指令表中有这个才读取
  if(d->m_socket->containsCmd(item->text(COL_PAGE_TREE_NAME)))
  {
    rv=d->m_socket->genCmdRead(item->text(COL_PAGE_TREE_NAME),axisInx,rOk);
    if(!rOk)
      return rOk;

    if(type=="Uint16")
    {
      quint16 value=rv;
      item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
    }
    else if(type=="int16")
    {
      qint16 value=rv;
      item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
    }
    else if(type=="Uint32")
    {
      quint32 value=rv;
      item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
    }
    else if(type=="int32")
    {
      qint32 value=rv;
      item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
    }
    else if(type=="Uint64")
    {
      quint64 value=rv;
      item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
    }
    else if(type=="int64")
    {
      qint64 value=rv;
      item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
    }
    else
    {
      quint16 value=rv;
      item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
    }
  }

  return rOk;
}

bool SevDevice::writeGenItemRAM(quint16 axisInx, QTreeWidgetItem *item)
{
  //1 调通用指令写原数

  Q_D(SevDevice);

  double value;
  bool rOk=true;

  if(d->m_socket->containsCmd(item->text(COL_PAGE_TREE_NAME)))
  {
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    rOk=d->m_socket->genCmdWrite(item->text(COL_PAGE_TREE_NAME),(quint64)value,axisInx);
  }
  return rOk;
}

bool SevDevice::readGenPageRAM(quint16 axisInx, QTreeWidget *pageTree)
{
  //1 调通用指令读取原数

  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;

  QTreeWidgetItemIterator it(pageTree);
  QTreeWidgetItem *item;
  bool rOk=true;
  while (*it)
  {
    item=(*it);
    rOk=readGenItemRAM(axisInx,item);
    if(!rOk)
      break;
    it++;
  }
  return rOk;
}

bool SevDevice::writeGenPageRAM(quint16 axisInx, QTreeWidget *pageTree)
{
  //1 调通用指令写原数

  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;

  bool checkOk=true;
  checkOk=checkParameters(axisInx,pageTree);
  if(!checkOk)
    return false;


  QTreeWidgetItemIterator it(pageTree);
  QTreeWidgetItem *item;
  bool rOk=true;
  while (*it)
  {
    item=(*it);
    rOk=writeGenItemRAM(axisInx,item);
    if(rOk)
    {
      rOk=readGenItemRAM(axisInx,item);
      emit itemRangeValid(item,(int)OptFace::EDIT_TEXT_STATUS_DEFAULT);
    }
    else
    {
      QMessageBox::warning(0,tr("Write Error"),tr("Write Config Parameter Error:%1 ").arg(item->text(GT::COL_PAGE_TREE_NAME)));
      break;
    }
    it++;
  }
  return rOk;
}

bool SevDevice::writeItemFlash(quint16 axisInx, QTreeWidgetItem *item)
{
  Q_D(SevDevice);
  return d->m_socket->writeItemFlash(axisInx,item);
}

bool SevDevice::readItemFlash(quint16 axisInx, QTreeWidgetItem *item)
{
  Q_D(SevDevice);
  return d->m_socket->readItemFlash(axisInx,item);
}

bool SevDevice::clearAlarm(quint16 axisInx)
{
  Q_D(SevDevice);
  if(isConnecting())
    return d->m_socket->clearAlarm(axisInx);
  else
    return true;
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
/*!
 * \brief SevDevice::checkStatus
 * \return true:连线正常 false断线异常
 */
bool SevDevice::checkNetStatus()
{
  Q_D(SevDevice);
  bool offline=true;

#if TEST_CHECKSTATUS
  QVector<quint8> errtest;
  for(int i=0;i<d->m_devConfig->m_axisNum;i++)
  {
    errtest.append(i%2);
  }
#endif

  for(int i=0;i<d->m_devConfig->m_axisNum;i++)
  {
    #if TEST_CHECKSTATUS
      quint64 ret=errtest.at(i);
    #elif TEST_CHECKSTATUS==0
      quint64 ret=genCmdRead(CMD_PRO_ALM_FLAG,i,offline);
//      qDebug()<<"read status "<<i<<"value="<<ret<<offline;
    #endif

    if(!offline)
    {
      emit netError(i);
      qDebug()<<"Emit netError"<<i<<"When the net is broken";
      break;
    }
    emit alarmError(d->m_devConfig->m_devId,i,(bool)ret);
  }


  return offline;
}

QString SevDevice::filePath() const
{
  Q_D(const SevDevice);
  return d->m_filePath;
}

void SevDevice::qmlTest()
{
  qDebug()<<"this is qml signals to device";
}

bool SevDevice::onReadPageFlash(int axis, QTreeWidget *pageTree)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;

  QTreeWidgetItemIterator it(pageTree);
  QTreeWidgetItem *item;
  bool rOk=true;
  while (*it)
  {
    item=(*it);
    rOk=d->m_socket->readItemFlash(axis,item);
    if(!rOk)
    {
      rOk=false;
      break;
    }
    it++;
  }
  return rOk;
}
bool SevDevice::onWritePageFlash(int axis, QTreeWidget *pageTree)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;

  bool checkOk=true;
  checkOk=checkParameters(axis,pageTree);
  if(!checkOk)
    return false;


  QTreeWidgetItemIterator it(pageTree);
  QTreeWidgetItem *item;
  bool writeOk=true;
  while (*it)
  {
    item=(*it);
    qDebug()<<"write item"<<item->text(GT::COL_PAGE_TREE_NAME)<<"value"<<item->text(GT::COL_PAGE_TREE_VALUE);

    writeOk=d->m_socket->writeItemFlash(axis,item);
    qDebug()<<"writeOk"<<writeOk;
    if(writeOk)
    {
      d->m_socket->readItemFlash(axis,item);
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
    QString msg=QString(tr("CheckPrm Error\n:%1 %2 is out of range %3 -- %4\nparamater save fail!")\
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
      QMessageBox::warning(0,tr("Prm Error"),tr("PowerBoard CheckPrm Error\n:%1 is out of range\nparamater save fail!").arg(name));
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
