#include "devcomrwriter.h"
#include "icom.h"
#include "pcdebug.h"
#include "rnnet.h"
#include "deviceconfig.h"
#include "deviceidhelper.h"
#include "sdtglobaldef.h"

#include "gtutils.h"
#include "qttreemanager.h"
#include "sdterror.h"

#include <QVector>
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>

using namespace ComDriver;
DevComRWriter::DevComRWriter(QObject *parent):IDevReadWriter(parent)
{

}

QList<DeviceConfig *>DevComRWriter::createConfig(void (*processCallback)(void *pbar,short *value),void *processbar,bool &isOk)
{
  isOk=true;

  //1 一种种通信方式试探，找到当前连接的通信方式
  QList<DeviceConfig *> list;
  ICom *com=openTragetCom(processCallback,processbar);
  if(com==NULL)
  {
    isOk=false;
    SdtError::instance()->errorStringList()->append(tr("OpenError:"));
    SdtError::instance()->errorStringList()->append(tr("  1 cable is not connect"));
    SdtError::instance()->errorStringList()->append(tr("  2 cable connet to wrong com"));
    SdtError::instance()->errorStringList()->append(tr("  3 device firmware error"));
    return list;
  }

  // 2 检查网卡是不是1000M
  bool is1000M=checkNetCardIs1000M(com);
  if(!is1000M)
  {
    com->close();
    delete com;
    com=NULL;
    isOk=false;
    return list;
  }

  QString name;
  std::string str=com->iComObjectName();
  name=QString::fromStdString(str);
  qDebug()<<"target com "<<name;

  DeviceConfig *config=NULL;
  if(com->iComType()==ICOM_TYPE_RNNET)
  {
    RnNet *rnNet=dynamic_cast<RnNet *>(com);
    std::vector<uint8_t> vtr=rnNet->broadcast();
    qDebug()<<"size"<<vtr.size();

    std::vector<uint8_t>::iterator it=vtr.begin();
    while(it!=vtr.end())
    {
      qDebug()<<"station ="<<(*it);
      ++it;
    }
    QVector<uint8_t> v;
    v=QVector<uint8_t>::fromStdVector(vtr);
    if(v.isEmpty())
    {
      isOk=false;
      SdtError::instance()->errorStringList()->append(tr("  1 RnNet broadcast return null station error"));
    }
    int i=0;
    foreach (uint8_t station, v)
    {
      rnNet->setRnStation(station);
      config=buildConfigFromCom(i,station,rnNet);
      if(config!=NULL)
      {
        list.append(config);
        qDebug()<<"DeviceConfig m_axisNum="<<config->m_axisNum;
        qDebug()<<"DeviceConfig m_pwrId="<<config->m_pwrId;
        qDebug()<<"DeviceConfig m_ctrId="<<config->m_ctrId;
        qDebug()<<"DeviceConfig m_comType="<<config->m_comType;
        qDebug()<<"DeviceConfig m_devId="<<config->m_devId;
        qDebug()<<"DeviceConfig m_fpgaId="<<config->m_fpgaId;
        qDebug()<<"DeviceConfig m_modeName="<<config->m_modeName;
        qDebug()<<"DeviceConfig m_typeName="<<config->m_typeName;
        qDebug()<<"DeviceConfig m_rnStationId="<<config->m_rnStationId;
      }
      else
      {
        isOk=false;
        SdtError::instance()->errorStringList()->append(tr("  RnNet station : %1 error!").arg(i));
        break;
      }
      i++;
    }
  }
  else//PcDebug 模式
  {
    config=buildConfigFromCom(0,-1,com);
    if(config!=NULL)
      list.append(config);
  }


  com->close();
  delete com;
  return list;
}

bool DevComRWriter::saveConfig(const DeviceConfig *config)
{
  Q_UNUSED(config);
  return true;
}

ICom *DevComRWriter::openTragetCom(void (*processCallback)(void *pbar,short *value),void *processbar)
{
  ICom *com=new RnNet("RnNet");
  errcode_t err=com->open(processCallback,processbar);
  if(err!=0)
  {
    com->close();
    delete com;
    com=new PcDebug("PcDebug");
    qDebug()<<"new com"<<QString::fromStdString(com->iComObjectName());
    err=com->open(processCallback,processbar);
    if(err!=0)
    {
      com->close();
      delete com;
      com=NULL;
    }
  }
  return com;
}

bool DevComRWriter::checkNetCardIs1000M(ICom *com)
{
  bool ok=true;
  NetCardInfo cardInfo=com->getNetCardInformation();
  if(cardInfo!=NET_1000M)
  {
    SdtError::instance()->errorStringList()->append(tr("Net Speed Error"));
    SdtError::instance()->errorStringList()->append(tr("  1 cable is not supported 1000M"));
    SdtError::instance()->errorStringList()->append(tr("  2 your computer netcom is not supported 1000M"));
    ok=false;
  }
  return ok;
}

DeviceConfig* DevComRWriter::buildConfigFromCom(quint8 devId, quint8 rnstation, ComDriver::ICom *com)
{
  DeviceIdHelper idHelper(com);
  DeviceConfig *config=NULL;
  bool pok=true;
  bool cok=true;
  bool vok=true;
  bool fok=true;
  quint32 pid,cid,fid;
  QString version;

  if(com->iComType()==ComDriver::ICOM_TYPE_PCDEBUG)//PcDebug就不支持读写I2c
  {
    pok=false;
  }
  else
  {
    qDebug()<<"ssssssssssss";
    pid= idHelper.readPwrId(pok);
    cid= idHelper.readCtrId(cok);
    version=idHelper.readVersion(vok);
    fid=idHelper.readFpgaId(fok);
  }


  if(pok&&cok&&vok&&fok)
  {
    config=new DeviceConfig(0);
    config->m_pwrId= pid;
    config->m_ctrId= cid;
    config->m_version=version;
    config->m_fpgaId=fid;
    config->m_comType=com->iComType();
    config->m_axisNum=idHelper.axisNumFromIdMap();
    config->m_devId=devId;

    config->m_modeName=idHelper.modeNameFromIdMap();
    config->m_typeName=idHelper.typeNameFromIdMap();
    config->m_rnStationId=rnstation;

    qDebug()<<"config->m_pwrId"<<config->m_pwrId;
    qDebug()<<"config->m_ctrId"<<config->m_ctrId;
    qDebug()<<"config->m_version"<<config->m_version;
    qDebug()<<"config->m_comType"<<config->m_comType;
    qDebug()<<"m_axisNum"<<config->m_axisNum;
    qDebug()<<"config->m_fpgaId"<<config->m_fpgaId;
    qDebug()<<"config->m_modeName"<<config->m_modeName;
    qDebug()<<"config->m_typeName"<<config->m_typeName;

    //加软件是否支持当前配置判断? 主要是查V129 V130 ...有没有在软件中
    //如果没有的话，自动选择一个比较新的版本（为了让客户用老的软件也可以调新的固件)
    bool support=true;
    support=checkSupport(config);
    if(!support)
    {
//      delete config;
//      config=NULL;
//      SdtError::instance()->errorStringList()->append(tr("your software is too old ,not support the current device\nplease update from\n\nhttp://www.googoltech.com.cn\n"));
    }
  }
  else
  {
    SdtError::instance()->errorStringList()->append(tr("\nError:"));
    QString solution=tr("\nSolution:\n");
    int i=1;
    if(!pok)
    {
      if(idHelper.databaseHasPwrId()==false)
      {
        SdtError::instance()->errorStringList()->append(tr("  %1 your SDT software is too old ,cannot find PowerBoard ID").arg(i++));
        solution.append(tr("Must update the SDT software\n"));
      }
      else
      {
        SdtError::instance()->errorStringList()->append(tr("  %1 read powerboard eeprom error").arg(i++));
      }
    }
    if(!cok)
      SdtError::instance()->errorStringList()->append(tr("  %1 read controlboard eeprom error").arg(i++));
    if(!vok)
      SdtError::instance()->errorStringList()->append(tr("  %1 read dsp version error").arg(i++));
    if(!fok)
      SdtError::instance()->errorStringList()->append(tr("  %1 read fpga version error").arg(i++));

    if(idHelper.databaseHasPwrId())
    {
      QString str1=tr(" manual to select the software toolbar:\nmore->option->autolaod->unchecked clicked apply\n");
      QString str2=tr("and then toolbar:new ....select your correct version");
      solution.append(str1);
      solution.append(str2);
    }
    SdtError::instance()->errorStringList()->append(solution);
    qDebug()<<"pok"<<pok<<"cok"<<cok<<"vok"<<vok<<"fok"<<fok;
  }

  return config;
}
void DevComRWriter::printfInfo(void *argv, short *v)
{
  int va=*v;
  printf("value=%d\n",va);
}


QTreeWidgetItem* DevComRWriter::findItemByText(QTreeWidgetItem*srcItem,const QString &text)
{
//  QTreeWidgetItem *child;
//  for(int i=0;i<srcItem->childCount();i++)
//  {
//    child=srcItem->child(i);
//    if(child->text(COL_NAME)==text)
//    {
//      break;
//    }
//    else
//      child=NULL;
//  }
//  return child;
  QTreeWidgetItem *item;
  QTreeWidgetItem *targetItem=NULL;
  QTreeWidgetItemIterator it(srcItem);
  while(*it)
  {
    item=(*it);
    if(item->text(COL_NAME)==text)
    {
      targetItem=item;
      qDebug()<<"find target item "<<targetItem->text(0);
      break;
    }
    it++;
  }
  return targetItem;
}
bool DevComRWriter::checkSupport(DeviceConfig *config)
{
  bool isFind=true;
  QString path=GTUtils::sysPath()+"SysMap/ConfigSelectTree.ui";
  QTreeWidget *selectTree=QtTreeManager::createTreeWidgetFromXmlFile(path);

  int index=config->m_comType;
  QTreeWidgetItem *item=selectTree->topLevelItem(index);
  QTreeWidgetItem *typeItem=findItemByText(item,config->m_typeName);
  if(typeItem!=NULL)
  {
    QTreeWidgetItem *modelItem=findItemByText(typeItem,config->m_modeName);
    if(modelItem!=NULL)
    {

      QTreeWidgetItem *verItem=findItemByText(modelItem,config->m_version);
      if(verItem==NULL)
      {
        qDebug()<<"cannot find current device :"<<config->m_version<<" auto set the lastest version"<<modelItem->child(modelItem->childCount()-1)->text(0);
        config->m_version=modelItem->child(modelItem->childCount()-1)->text(0);
        isFind=false;
      }
    }
    else
      isFind=false;
  }
  else
    isFind=false;

  delete selectTree;

  return isFind;
}
