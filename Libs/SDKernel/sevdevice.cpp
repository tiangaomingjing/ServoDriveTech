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
#include "sevsearchphasehelper.h"
#include "imaxprmassociationhelper.h"

#include <QTreeWidget>
#include <QStringList>
#include <QApplication>
#include <QDebug>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>


#define CMD_PRO_ALM_FLAG "gSevDrv.sev_obj.cur.pro.alm_flag"
#define FILENAME_PRM_PTY_TREE "PrmPrtyTree.xml"
#define CMD_SRC_SEL_NAME "gSevDrv.sev_obj.pos.seq.prm.cmd_src_sel"

#define PRM_FIRMWARE_UPDATE_FILE_NAME         "PrmFirmwareUpdate.xml"

#define TEST_CHECKSTATUS 0

#define CMD_MOT_NOS_KEY_NAME                  "gSevDrv.sev_obj.cur.mot.Nos_1"
#define CMD_POS_MKR_PRM_MAXSPD_NAME           "gSevDrv.sev_obj.pos.mkr.prm.maxspd"
#define CMD_POS_MKR_PRM_ACC_NAME              "gSevDrv.sev_obj.pos.mkr.prm.accrate"
#define CMD_POS_MKR_PRM_DEC_NAME              "gSevDrv.sev_obj.pos.mkr.prm.decrate"
#define CMD_VEL_ATN_FGD_NAME                  "gSevDrv.sev_obj.vel.atn.fgd"
#define CMD_VEL_ATN_FGP_NAME                  "gSevDrv.sev_obj.vel.atn.fgp"
#define CMD_VEL_ATN_FGI_NAME                  "gSevDrv.sev_obj.vel.atn.fgi"
#define CMD_VEL_ATN_FGN_NAME                  "gSevDrv.sev_obj.vel.atn.fgn"
#define CMD_VEL_ATN_FINISH_NAME               "gSevDrv.sev_obj.vel.atn.finish_flag"

//偶数轴的地址加32678
#define ADDR_POS_GEAR_PRM_ANU_0   13790
#define ADDR_POS_GEAR_PRM_B       13798

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
  m_barCount(0),
  m_imaxPrmAssociationHelper(NULL)
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
  GT::deepClearList(m_searchPhaseHelperList);
  delete m_imaxPrmAssociationHelper;
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

  QByteArray byte;
  byte.append(65+m_devConfig->m_devId);
  m_aliasName=QString::fromLatin1(byte);

  for(int i = 0;i<m_devConfig->m_axisNum;i++)
  {
    SevSearchPhaseHelper *ipaHelper = new SevSearchPhaseHelper(q_ptr,i,0);
    m_searchPhaseHelperList.append(ipaHelper);
    connect(ipaHelper,SIGNAL(ipaDone()),q_ptr,SIGNAL(ipaDone()));
    connect(ipaHelper,SIGNAL(ipaSearchPhaseInfo(int,QString)),q_ptr,SIGNAL(ipaSearchPhaseInfo(int,QString)));
    connect(ipaHelper,SIGNAL(ipaWarningMsg(QString)),q_ptr,SIGNAL(ipaWarningMsg(QString)));
  }

  m_imaxPrmAssociationHelper = new ImaxPrmAssociationHelper(q_ptr);

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
  emit connectionChanged(d->m_connected);
  return d->m_connected;
}

void SevDevice::disableConnection()
{
  Q_D(SevDevice);
  emit connectionChanged(false);
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
  if(d->m_socket->isConnected()==false)
  {
    isOk = true;
    return 0;
  }
  return d->m_socket->genCmdRead(cmdReadName,axisIndex,isOk);
}

bool SevDevice::genCmdWrite(const QString &cmdWriteName,quint64 value,qint16 axisIndex)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return true;
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
//      qDebug()<<"int16 value = "<<value;
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

//  bool checkOk=true;
//  checkOk=checkPageParameters(axisInx,pageTree);
//  if(!checkOk)
//    return false;


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

bool SevDevice::writePageItemFlash(quint16 axisInx, QTreeWidgetItem *item)
{
  Q_D(SevDevice);
  return d->m_socket->writePageItemFlash(axisInx,item);
}

bool SevDevice::readPageItemFlash(quint16 axisInx, QTreeWidgetItem *item)
{
  Q_D(SevDevice);
    return d->m_socket->readPageItemFlash(axisInx,item);
}

bool SevDevice::writePrmItemFlash(quint16 axisInx, QTreeWidgetItem *item)
{
  Q_D(SevDevice);
  return d->m_socket->writePrmItemFlash(axisInx,item);
}

bool SevDevice::readPrmItemFlash(quint16 axisInx, QTreeWidgetItem *item)
{
  Q_D(SevDevice);
    return d->m_socket->readPrmItemFlash(axisInx,item);
}

bool SevDevice::writeAdvFlash(quint16 axisInx, QTreeWidgetItem *item)
{
    Q_D(SevDevice);
    return d->m_socket->writeAdvItemFlash(axisInx, item);
}

bool SevDevice::writeAdvRam(quint16 axisInx, QTreeWidgetItem *item)
{
    Q_D(SevDevice);
    return d->m_socket->writeAdvItemRam(axisInx, item);
}

bool SevDevice::readAdvFlash(quint16 axisInx, QTreeWidgetItem *item)
{
    Q_D(SevDevice);
    return d->m_socket->readAdvItemFlash(axisInx, item);
}

bool SevDevice::readAdvRam(quint16 axisInx, QTreeWidgetItem *item)
{
    Q_D(SevDevice);
  return d->m_socket->readAdvItemRam(axisInx, item);
}

bool SevDevice::readAdvRam(quint16 axisInx, quint16 offset, quint16 base, int bytesNum, double &result)
{
  Q_D(SevDevice);
return d->m_socket->readAdvItemRam(axisInx, offset,base,bytesNum,result);
}

bool SevDevice::startPlot(const ComDriver::PlotControlPrm &ctrPrm)
{
  Q_D(SevDevice);
  return d->m_socket->startPlot(ctrPrm);
}

bool SevDevice::stopPlot(const ComDriver::PlotControlPrm &ctrPrm)
{
  Q_D(SevDevice);
  return d->m_socket->stopPlot(ctrPrm);
}

bool SevDevice::getPlotData(const ComDriver::PlotControlPrm &ctrPrm, ComDriver::CurveList &curveList)
{
  Q_D(SevDevice);
  return d->m_socket->getPlotData(ctrPrm,curveList);
}

bool SevDevice::clearAlarm(quint16 axisInx)
{
  Q_D(SevDevice);
  if(isConnecting())
    return d->m_socket->clearAlarm(axisInx);
  else
    return true;
}

QString SevDevice::aliasName() const
{
  Q_D(const SevDevice);
  return d->m_aliasName;
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

void SevDevice::resetDevId(quint32 id)
{
  Q_D(SevDevice);
  d->m_devConfig->m_devId=id;
  QByteArray byte;
  byte.append(65+d->m_devConfig->m_devId);
  d->m_aliasName=QString::fromLatin1(byte);
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

QTreeWidget *SevDevice::axisTreeSource(int axis, const QString &name) const
{
  Q_D(const SevDevice);
  return d->m_dspMap->axisTreeWidget(axis,name);
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
  bool online=true;

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
      quint64 ret=genCmdRead(CMD_PRO_ALM_FLAG,i,online);
//      qDebug()<<"read status "<<i<<"value="<<ret<<online;
    #endif

    if(!online)
    {
      emit connectionChanged(false);
      emit netError(i);
      qDebug()<<"Emit netError"<<i<<"When the net is broken";
      break;
    }
    emit alarmError(d->m_devConfig->m_devId,i,(bool)ret);
    GTUtils::delayms(5);
  }


  return online;
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

bool SevDevice::axisServoIsOn(quint16 axisInx)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;
  return d->m_socket->axisServoIsOn(axisInx);
}

void SevDevice::setAxisServoOn(quint16 axisInx , bool enable)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;

  d->m_socket->setAxisServoOn(axisInx,enable);
}

int SevDevice::currentTaskServoMode(quint16 axisInx)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return 0;

  return d->m_socket->currentTaskServoMode(axisInx);
}

void SevDevice::setCurrentTaskServoMode(quint16 axisInx, int mode)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;

  d->m_socket->setCurrentTaskServoMode(axisInx,mode);
}

void SevDevice::setControlSrc(quint16 axisInx, GT::SevControlSrc ctlSrc)
{
  int ctlId = ctlSrc;
  genCmdWrite(CMD_SRC_SEL_NAME,ctlId,axisInx);
}

GT::SevControlSrc SevDevice::controlSrc(quint16 axisInx)
{
  bool isOK = true;
  int src = genCmdRead(CMD_SRC_SEL_NAME,axisInx,isOK);
  return (GT::SevControlSrc)src;
}

void SevDevice::cmdSetPosAdjRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setPosAdjRef(axisInx,value);
}

void SevDevice::cmdSetUaRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setUaRef(axisInx,value);
}

void SevDevice::cmdSetUbRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setUbRef(axisInx,value);
}

void SevDevice::cmdSetUcRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setUcRef(axisInx,value);
}

void SevDevice::cmdSetUdRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setUdRef(axisInx,value);
}

void SevDevice::cmdSetUqRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setUqRef(axisInx,value);
}

void SevDevice::cmdSetIdRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setIdRef(axisInx,value);
}

void SevDevice::cmdSetIqRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setIqRef(axisInx,value);
}

void SevDevice::cmdSetSpdRef(quint16 axisInx, double value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setSpdRef(axisInx,value);
}

void SevDevice::cmdSetPosRef(quint16 axisInx, qint32 value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return ;
  d->m_socket->m_com->setPosRef(axisInx,value);
}

bool SevDevice::cmdGetSpdFbPercent(quint16 axisInx, double &value)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;
  int ret =0;
  ret = d->m_socket->m_com->getSpdFb(axisInx,value);
  return ret ==0;
}

bool SevDevice::searchPhaseStart(quint16 axisInx, int value)
{
  Q_D(SevDevice);
  return d->m_searchPhaseHelperList.at(axisInx)->searchPhaseStart(value);
}

bool SevDevice::imaxPrmAssociationActive(quint16 axisInx)
{
  //gain =shunt (64424512)*dspversionfactor (2)/电阻值rValue
  //k = gain / imaxValue ;
  //shunt dspversionfactor 的数据来自 PrmImaxAssosiation.xml Motor  每个版本中dspversionfactor可能不一样
  //rValue 的数据来自刘超文功率板的PB.xml采样电阻值
  //最后计算的ka kb kc 要写到 PrmImaxAssosiation.xml记录中 ia ib ic
  Q_D(SevDevice);
  return d->m_imaxPrmAssociationHelper->active(axisInx);
}

bool SevDevice::resetDSP()
{
  Q_D(SevDevice);
  bool ret = true;
  emit dspReset();
  GTUtils::delayms(200);

  //到PrmFirmwareUpdate 找 dspNumber
  int dspNum = 1;
  QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(d->m_filePath + PRM_FIRMWARE_UPDATE_FILE_NAME);
  if(tree != NULL)
    dspNum = tree->topLevelItem(0)->child(ROW_PRM_FIRM_UPDATE_DEVICE_DSP)->text(1).toInt();
  delete tree;

  int tryCount = 1000;
  for(int i=0;i<dspNum;i++)
  {
    ComDriver::errcode_t err = d->m_socket->comObject()->resetDSP(i);
    if(err != 0)
    {
      err = d->m_socket->comObject()->resetDSP(i);
      if(err !=0)
      {
        ret = false;
        break;
      }
    }
    initProgressInfo(0,tr("reset dsp =%1").arg(i+1));

    int tryUse = 0;
    bool finish = false;
    double inc = 100.0/tryCount;
    do
    {
      finish = d->m_socket->comObject()->checkResetFinish(i,err);
      initProgressInfo(tryUse*inc,tr("dsp =%1 Reset Flag_Finish checking......").arg(i+1));
      GTUtils::delayms(20);
      tryUse ++;
      qDebug()<<"DSP = "<<i<<"tryUse = "<<tryUse<<"finish = "<<finish;
    }while((tryUse<tryCount)&&(finish == false));

    if(tryUse>=tryCount)
    {
      ret = false;
      break;
    }
  }

  return ret ;
}

bool SevDevice::readPageFlash(int axis, QTreeWidget *pageTree)
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
    rOk=d->m_socket->readPageItemFlash(axis,item);
    if(!rOk)
    {
      rOk=false;
      break;
    }
    it++;
  }
  return rOk;
}
bool SevDevice::writePageFlash(int axis, QTreeWidget *pageTree)
{
  Q_D(SevDevice);
  if(d->m_socket->isConnected()==false)
    return false;

//  bool checkOk=true;
//  checkOk=checkPageParameters(axis,pageTree);
//  if(!checkOk)
//    return false;


  QTreeWidgetItemIterator it(pageTree);
  QTreeWidgetItem *item;
  bool writeOk=true;
  while (*it)
  {
    item=(*it);
    qDebug()<<"write item"<<item->text(GT::COL_PAGE_TREE_NAME)<<"value"<<item->text(GT::COL_PAGE_TREE_VALUE);

    writeOk=d->m_socket->writePageItemFlash(axis,item);
    qDebug()<<"writeOk"<<writeOk;
    if(writeOk)
    {
      qDebug()<<"read 1";
      d->m_socket->readPageItemFlash(axis,item);
      emit itemRangeValid(item,(int)OptFace::EDIT_TEXT_STATUS_DEFAULT);
      qDebug()<<"read 2";
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

bool SevDevice::checkPagePropertyParameters(QTreeWidgetItem *item)
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
  //qDebug()<<"name"<<name;

  if(limit->contains(name))
  {
    double min,max,value=0;
    value=item->text(GT::COL_PAGE_TREE_VALUE).toDouble();
    min=limit->value(name).min;
    max=limit->value(name).max;
    qDebug()<<"name"<<name<<"value"<<value<<"max"<<max<<"min"<<min;
    if(!(value>=min&&value<=max))
    {
      checked=false;
      emit itemRangeValid(item,(int)OptFace::EDIT_TEXT_STATUS_ERROR);
      QMessageBox::warning(0,tr("Prm Error"),tr("PowerBoard CheckPrm Error\n:%1 is out of range\nparamater save fail!").arg(name));
    }
  }
  return checked;
}

/**
 * @brief SevDevice::checkPageParameters
 * @param axis
 * @param tree
 * @return  返回值 true :通过检查  false：没有通过检查
 */
bool SevDevice::checkPageParameters(int axis, QTreeWidget *tree)
{
  bool isOk=true;
  QTreeWidgetItem *item;
  for(int i=0;i<tree->topLevelItemCount();i++)
  {
      //1 检查输入值是否在约束范围内
      item=tree->topLevelItem(i);
      isOk=checkPagePropertyParameters(item);
      if(!isOk)
      {
        qCritical()<<"check error "<<item->text(0);
        break;
      }
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

quint64 SevDevice::genCmdReadNos(int axisInx, bool &isOk)
{
  quint64 v=genCmdRead(CMD_MOT_NOS_KEY_NAME,axisInx,isOk);
  return v;
}

quint64 SevDevice::genCmdReadAutoTurnningFgd(int axisInx, bool &isOk)
{
  quint64 ret = genCmdRead(CMD_VEL_ATN_FGD_NAME,axisInx,isOk);
  qDebug()<<"fgd = "<<ret;
  return ret;
}

quint64 SevDevice::genCmdReadAutoTurnningFgi(int axisInx, bool &isOk)
{
  quint64 ret = genCmdRead(CMD_VEL_ATN_FGI_NAME,axisInx,isOk);
  qDebug()<<"fgi = "<<ret;
  return ret;
}

quint64 SevDevice::genCmdReadAutoTurnningFgp(int axisInx, bool &isOk)
{
  quint64 ret = genCmdRead(CMD_VEL_ATN_FGP_NAME,axisInx,isOk);
  qDebug()<<"fgp = "<<ret;
  return ret;
}

quint64 SevDevice::genCmdReadAutoTurnningFgn(int axisInx, bool &isOk)
{
  quint64 ret = genCmdRead(CMD_VEL_ATN_FGN_NAME,axisInx,isOk);
  qDebug()<<"fgn = "<<ret;
  return ret;
}

bool SevDevice::genCmdAutoTurnningFinishFlag(int axisInx, bool &isOk)
{
  return genCmdRead(CMD_VEL_ATN_FINISH_NAME,axisInx,isOk);
}

bool SevDevice::genCmdWritePlanSpdMax(int axisInx, quint64 value)
{
    qDebug()<<"write spd max "<<value;
  return genCmdWrite(CMD_POS_MKR_PRM_MAXSPD_NAME,value,axisInx);
}

bool SevDevice::genCmdWritePlanSpdAcc(int axisInx, quint64 value)
{
  return genCmdWrite(CMD_POS_MKR_PRM_ACC_NAME,value,axisInx);
}

bool SevDevice::genCmdWritePlanSpdDec(int axisInx, quint64 value)
{
  return genCmdWrite(CMD_POS_MKR_PRM_DEC_NAME,value,axisInx);
}

bool SevDevice::writeGearPrm(quint16 axisInx, qint32 a, qint32 b)
{
  Q_D(SevDevice);
  if(isConnecting() == false)
    return false;

  quint16 addr_a = ADDR_POS_GEAR_PRM_ANU_0;
  quint16 addr_b = ADDR_POS_GEAR_PRM_B;
  if(axisInx%2 !=0)
  {
    addr_a += 32768;
    addr_b += 32768;
  }
  ComDriver::errcode_t err = 0;
  err = d->m_socket->comObject()->writeFLASH32(axisInx,addr_a,0,a);
  err = d->m_socket->comObject()->writeFLASH32(axisInx,addr_b,0,b);
  return err == 0;
}

bool SevDevice::readGearPrm(quint16 axisInx, qint32 &a, qint32 &b)
{
  Q_D(SevDevice);
  if(isConnecting() == false)
    return false;

  quint16 addr_a = ADDR_POS_GEAR_PRM_ANU_0;
  quint16 addr_b = ADDR_POS_GEAR_PRM_B;
  if(axisInx%2 !=0)
  {
    addr_a += 32768;
    addr_b += 32768;
  }
  ComDriver::errcode_t err = 0;
  ComDriver::int32_t va = 0;
  ComDriver::int32_t vb = 0;
  err = d->m_socket->comObject()->readFLASH32(axisInx,addr_a,0,va);
  err = d->m_socket->comObject()->readFLASH32(axisInx,addr_b,0,vb);
  a = va;
  b = vb;
  return err == 0;
}

bool SevDevice::checkLoadParameters(QTreeWidget *tree, int itemNum)
{
    Q_D(SevDevice);
    d->m_barCount = 0;
    bool isOk=true;
        qDebug()<<"check";
        QString prmPtyPath = GTUtils::sysPath() + typeName() + "/" + modelName() + "/" + versionName() + "/" + FILENAME_PRM_PTY_TREE;
        QTreeWidget* prmPtyTree = QtTreeManager::createTreeWidgetFromXmlFile(prmPtyPath);
        for (int i = 0; i < tree->topLevelItemCount(); i++) {
            isOk = checkLoadItemParameters(i, tree->topLevelItem(i), prmPtyTree, itemNum);
            if (!isOk) {
                return isOk;
            }
        }
    return isOk;
}

bool SevDevice::writeXml(quint8 axis, const QStringList &fileNameList, QList<int> fileTypeList, int file_num, void (*processCallBack)(void *, short *), void *ptrv, short &progress)
{
    Q_D(SevDevice);
    return d->m_socket->writeXml(axis, fileNameList, fileTypeList, file_num, processCallBack, ptrv, progress);
}

bool SevDevice::readXml(quint8 axis, const QStringList &fileNameList, QList<int> fileTypeList, int file_num, void (*processCallBack)(void *, short *), void *ptrv, short &progress)
{
    Q_D(SevDevice);
    return d->m_socket->readXml(axis, fileNameList, fileTypeList, file_num, processCallBack, ptrv, progress);
}

bool SevDevice::checkLoadItemParameters(int axis, QTreeWidgetItem *item, QTreeWidget *prmTree, int itemNum)
{
    Q_D(SevDevice);
    if (d->m_barCount % 10 == 0) {
        emit initProgressInfo(d->m_barCount * 100 / itemNum, tr("Checking axis%1").arg(QString::number(axis + 1)) + item->text(GT::COL_FLASH_ALLAXIS_NAME));
        qApp->processEvents();
    }
    d->m_barCount++;
    bool isOk = true;
    isOk = checkLoadPropertyParameters(item, prmTree);
    if (!isOk) {
        return isOk;
    }
    QMap<QString ,PowerBoardLimit> limit;
    if(!(d->m_pwrBoard->pwrLimitMapList()->isEmpty()))
    {
        limit = d->m_pwrBoard->pwrLimitMapList()->at(axis);
        isOk = checkPowerBoardParameters(item, &limit);
        if (!isOk) {
            return isOk;
        }
    }
    for (int i = 0; i < item->childCount(); i++) {
        isOk = checkLoadItemParameters(axis, item->child(i), prmTree, itemNum);
        if (!isOk) {
            return isOk;
        }
    }
    return isOk;
}

bool SevDevice::checkLoadPropertyParameters(QTreeWidgetItem *item, QTreeWidget* prmTree)
{
    bool checked=true;
    QString name = item->text(GT::COL_FLASH_ALLAXIS_NAME);
    double value ,min,max;
    value=item->text(GT::COL_FLASH_ALLAXIS_VALUE).toDouble();

    QTreeWidgetItem* prmItem = GTUtils::findItem(name, prmTree, GT::COL_PRM_PRTY_NAME);
    if (prmItem == NULL) {
        return true;
    }
    min = prmItem->text(GT::COL_PRM_PRTY_MIN).toDouble();
    max = prmItem->text(GT::COL_PRM_PRTY_MAX).toDouble();
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
