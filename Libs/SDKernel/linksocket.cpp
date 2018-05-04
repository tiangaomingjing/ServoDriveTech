#include "linksocket.h"
#include "icom.h"
#include "sevdeviceprivate_p.h"
#include "pcdebug.h"
#include "rnnet.h"
#include "deviceconfig.h"
#include "sdtglobaldef.h"
#include "generalcmd.h"
#include "qttreemanager.h"
#include "cmdmanager.h"

#include <QTreeWidgetItem>
#include <QDebug>

#define STR_MARK_ALL "all"
#define STR_MARK_BIT "bit"

using namespace ComDriver;
using namespace GT;

LinkSocket::LinkSocket(SevDevicePrivate *sev, QObject *parent):QObject(parent),q_ptr(sev),m_isConnected(false),
  m_tryWriteCount(3)
{
  switch(sev->m_devConfig->m_comType)
  {
  case ICOM_TYPE_PCDEBUG:
    m_com=new PcDebug();
    qDebug()<<"com is pcdebug";
    break;
  case ICOM_TYPE_RNNET:
  {
    RnNet *rnNet=new RnNet();
    rnNet->setRnStation(sev->m_devConfig->m_rnStationId);
    m_com=rnNet;
    qDebug()<<"com is rn net";
  }
    break;
  case ICOM_TYPE_SOCKET:
    break;
  case ICOM_TYPE_VIRTUAL:
    break;
  default:
    break;
  }

  m_genCmd=new GeneralCmd(m_com);
  QString gcmdPath=sev->m_filePath+"cmd/GeneralCmd.xml";
  QTreeWidget *cmdTree=QtTreeManager::createTreeWidgetFromXmlFile(gcmdPath);
  m_genCmd->fillCmdMaps(cmdTree);
  m_cmdManager = new CmdManager(this);
  delete cmdTree;
}

LinkSocket::~LinkSocket()
{
  GT::deletePtrObject(m_genCmd);
}


bool LinkSocket::connect(void (*processCallBack)(void *argv,short* value),void *uiProcessBar)
{
  ComDriver::errcode_t err=m_com->open(processCallBack,uiProcessBar);
  if(err==0)
    m_isConnected=true;
  else
    m_isConnected=false;
  return m_isConnected;
}
void LinkSocket::disConnect()
{
  m_com->close();
  m_isConnected=false;
}

QString LinkSocket::socketName()const
{
  return QString::fromStdString(m_com->iComObjectName());
}
quint8 LinkSocket::socketTypeId()const
{
  return quint8(m_com->iComType());
}

bool LinkSocket::isConnected() const
{
  return m_isConnected;
}

bool LinkSocket::readItemFlash(int axis,QTreeWidgetItem *item)
{
  if(!m_isConnected)
    return true;
  QString type;
  uint16_t addr;
  uint8_t axisInx=axis;
  type=item->text(COL_PAGE_TREE_TYPE);
  addr=item->text(COL_PAGE_TREE_ADDR).toUShort();
  if(type=="Uint16")
  {
    int16_t value;
    m_com->readFLASH16(axisInx,addr,0,value);
    item->setText(COL_PAGE_TREE_VALUE,QString::number((uint16_t)value));
  }
  else if(type=="int16")
  {
    int16_t value;
    m_com->readFLASH16(axisInx,addr,0,value);
    item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
  }
  else if(type=="Uint32")
  {
    int32_t value;
    m_com->readFLASH32(axisInx,addr,0,value);
    item->setText(COL_PAGE_TREE_VALUE,QString::number((uint32_t)value));
  }
  else if(type=="int32")
  {
    int32_t value;
    m_com->readFLASH32(axisInx,addr,0,value);
    item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
  }
  else if(type=="Uint64")
  {
    int64_t value;
    m_com->readFLASH64(axisInx,addr,0,(int64_t)value);
    item->setText(COL_PAGE_TREE_VALUE,QString::number((uint64_t)value));
  }
  else if(type=="int64")
  {
    int64_t value;
    m_com->readFLASH64(axisInx,addr,0,value);
    item->setText(COL_PAGE_TREE_VALUE,QString::number(value));
  }
  else
  {
    int16_t value;
    m_com->readFLASH16(axisInx,addr,0,value);
    item->setText(COL_PAGE_TREE_VALUE,QString::number((uint16_t)value));
  }
  return true;
}
bool LinkSocket::writeItemFlash(int axis,QTreeWidgetItem *item)
{
  if(!m_isConnected)
    return true;
  QString type;
  uint16_t addr;
  ComDriver::errcode_t err;
  uint8_t axisInx=axis;
  type=item->text(COL_PAGE_TREE_TYPE);
  addr=item->text(COL_PAGE_TREE_ADDR).toUShort();
  if(type=="Uint16")
  {
    uint16_t wv;
    int16_t rv;
    double value=0;
//    wv=item->text(COL_PAGE_TREE_VALUE).toUShort();//这个不能用，因为如果是text是浮点数，转化后为0 如10.00.toUShort =0
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    wv=(uint16_t)value;
    quint8 tryCount=0;
    do{
      err=m_com->writeFLASH16(axisInx,addr,0,(int16_t)wv);
      m_com->readFLASH16(axisInx,addr,0,rv);
      tryCount++;
    }while(((uint16_t)rv!=wv)&&(tryCount<m_tryWriteCount));
    qDebug()<<"tryCount"<<tryCount<<tr("write,read(%1,%2)").arg(wv).arg(rv);
    if(tryCount>=m_tryWriteCount)
      return false;
  }
  else if(type=="int16")
  {
    int16_t wv;
    int16_t rv;
    double value=0;
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    wv=(int16_t)value;

    quint8 tryCount=0;
    do{
      err=m_com->writeFLASH16(axisInx,addr,0,wv);
      m_com->readFLASH16(axisInx,addr,0,rv);
      tryCount++;
    }while((rv!=wv)&&(tryCount<m_tryWriteCount));
    if(tryCount>=m_tryWriteCount)
      return false;
  }
  else if(type=="Uint32")
  {
    uint32_t wv;
    int32_t rv;
    double value=0;
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    wv=(uint32_t)value;

    quint8 tryCount=0;
    do{
      err=m_com->writeFLASH32(axisInx,addr,0,(int32_t)wv);
      m_com->readFLASH32(axisInx,addr,0,rv);
      tryCount++;
    }while(((uint32_t)rv!=wv)&&(tryCount<m_tryWriteCount));
    if(tryCount>=m_tryWriteCount)
      return false;
  }
  else if(type=="int32")
  {
    int32_t wv;
    int32_t rv;
    double value=0;
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    wv=(int32_t)value;

    quint8 tryCount=0;
    do{
      err=m_com->writeFLASH32(axisInx,addr,0,wv);
      m_com->readFLASH32(axisInx,addr,0,rv);
      tryCount++;
    }while((rv!=wv)&&(tryCount<m_tryWriteCount));
    if(tryCount>=m_tryWriteCount)
      return false;
  }
  else if(type=="Uint64")
  {
    uint64_t wv;
    int64_t rv;
    double value=0;
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    wv=(uint64_t)value;

    quint8 tryCount=0;
    do{
      err=m_com->writeFLASH64(axisInx,addr,0,(int64_t)wv);
      m_com->readFLASH64(axisInx,addr,0,rv);
      tryCount++;
    }while(((uint64_t)rv!=wv)&&(tryCount<m_tryWriteCount));
    if(tryCount>=m_tryWriteCount)
      return false;
  }
  else if(type=="int64")
  {
    int64_t wv;
    int64_t rv;
    double value=0;
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    wv=(int64_t)value;

    quint8 tryCount=0;
    do{
      err=m_com->writeFLASH64(axisInx,addr,0,wv);
      m_com->readFLASH64(axisInx,addr,0,rv);
      tryCount++;
    }while((rv!=wv)&&(tryCount<m_tryWriteCount));
    if(tryCount>=m_tryWriteCount)
      return false;
  }
  else
  {
    uint16_t wv;
    int16_t rv;
    double value=0;
    value=item->text(COL_PAGE_TREE_VALUE).toDouble()+0.5;
    wv=(uint16_t)value;

    quint8 tryCount=0;
    do{
      err=m_com->writeFLASH16(axisInx,addr,0,(int16_t)wv);
      m_com->readFLASH16(axisInx,addr,0,rv);
      tryCount++;
    }while(((uint16_t)rv!=wv)&&(tryCount<m_tryWriteCount));
    if(tryCount>=m_tryWriteCount)
      return false;
  }
  return true;
}

bool LinkSocket::readUiItemFlash(int axisInx, QTreeWidgetItem *item)
{
    if (isConnected()) {
        if (item->text(GT::COL_FR_ADDRESS).compare("-1") != 0) {
            uint16_t ofst = item->text(GT::COL_FR_ADDRESS).toUShort();
            QString itemType = item->text(GT::COL_FR_TYPE);
            uint8_t page = 0;
            int16_t ret = 0;
            if (itemType.compare("int32") == 0) {
                int32_t value;
                ret = m_com->readFLASH32(axisInx, ofst, page, value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("Uint32") == 0) {
                uint32_t value;
                ret = m_com->readFLASH32(axisInx, ofst, page, (int32_t&)value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("int64") == 0) {
                int64_t value;
                ret = m_com->readFLASH64(axisInx, ofst, page, value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("Uint64") == 0) {
                uint64_t value;
                ret = m_com->readFLASH64(axisInx, ofst, page, (int64_t&)value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("int16") == 0) {
                int16_t value;
                ret = m_com->readFLASH16(axisInx, ofst, page, value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else {
                uint16_t value;
                ret = m_com->readFLASH16(axisInx, ofst, page, (int16_t&)value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            }
            if (ret != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool LinkSocket::writeUiItemFlash(int axisInx, QTreeWidgetItem *item)
{
    if (isConnected()) {
        if (item->text(GT::COL_FR_ADDRESS).compare("-1") != 0) {
            uint16_t ofst = item->text(GT::COL_FR_ADDRESS).toUShort();
            QString itemType = item->text(GT::COL_FR_TYPE);
            uint8_t page = 0;
            errcode_t ret = 0;
            if (itemType.compare("Uint32") == 0) {
                uint32_t value = item->text(GT::COL_FR_VALUE).toULong();
                ret = m_com->writeFLASH32(axisInx, ofst, page, value);
    //            ret = m_com->readFLASH32(axisInx, ofst, page, (int32_t&)value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("int32") == 0) {
                int32_t value = item->text(GT::COL_FR_VALUE).toLong();
                ret = m_com->writeFLASH32(axisInx, ofst, page, value);
    //            ret = m_com->readFLASH32(axisInx, ofst, page, value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("Uint64") == 0) {
                uint64_t value = item->text(GT::COL_FR_VALUE).toULongLong();
                ret = m_com->writeFLASH64(axisInx, ofst, page, value);
    //            ret = m_com->readFLASH64(axisInx, ofst, page, (int64_t&)value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("int64") == 0) {
                int64_t value = item->text(GT::COL_FR_VALUE).toLongLong();
                ret = m_com->writeFLASH64(axisInx, ofst, page, value);
    //            ret = m_com->readFLASH64(axisInx, ofst, page, value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("int16") == 0) {
                int16_t value = item->text(GT::COL_FR_VALUE).toShort();
                ret = m_com->writeFLASH16(axisInx, ofst, page, value);
    //            ret = m_com->readFLASH16(axisInx, ofst, page, value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else {
                uint16_t value = item->text(GT::COL_FR_VALUE).toUShort();
                ret = m_com->writeFLASH16(axisInx, ofst, page, value);
    //            ret = m_com->readFLASH16(axisInx, ofst, page, (int16_t&)value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            }
            if (ret != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool LinkSocket::readUiItemRam(int axisInx, QTreeWidgetItem *item)
{
    if (isConnected()) {
        if (item->text(GT::COL_FR_ADDRESS).compare("-1") != 0) {
            uint16_t ofst = item->text(GT::COL_FR_ADDRESS).toUShort();
            QString itemType = item->text(GT::COL_FR_TYPE);
            QStringList keyList = item->text(GT::COL_FR_NAME).split(".");
            QString key = keyList.at(0);
            uint8_t page = m_cmdManager->getValue(key);
            int16_t ret = 0;
            if (itemType.compare("int32") == 0) {
                int32_t value;
                ret = m_com->readRAM32(axisInx, ofst, page, value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("Uint32") == 0) {
                uint32_t value;
                ret = m_com->readRAM32(axisInx, ofst, page, (int32_t&)value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("int64") == 0) {
                int64_t value;
                ret = m_com->readRAM64(axisInx, ofst, page, value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("Uint64") == 0) {
                uint64_t value;
                ret = m_com->readRAM64(axisInx, ofst, page, (int64_t&)value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else if (itemType.compare("int16") == 0) {
                int16_t value;
                ret = m_com->readRAM16(axisInx, ofst, page, value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            } else {
                uint16_t value;
                ret = m_com->readRAM16(axisInx, ofst, page, (int16_t&)value);
                if (ret == 0) {
                    item->setText(GT::COL_FR_VALUE, QString::number(value));
                }
            }
            if (ret != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool LinkSocket::writeUiItemRam(int axisInx, QTreeWidgetItem *item)
{
    if (isConnected()) {
        if (item->text(GT::COL_FR_ADDRESS).compare("-1") != 0) {
            uint16_t ofst = item->text(GT::COL_FR_ADDRESS).toUShort();
            QString itemType = item->text(GT::COL_FR_TYPE);
            errcode_t ret = 0;
            QStringList keyList = item->text(GT::COL_FR_NAME).split(".");
            QString key = keyList.at(0);
            uint8_t page = m_cmdManager->getValue(key);
            if (itemType.compare("Uint32") == 0) {
                uint32_t value = item->text(GT::COL_FR_VALUE).toULong();
                ret = m_com->writeRAM32(axisInx, ofst, page, value);
    //            ret = m_com->readRAM32(axisInx, ofst, page, (int32_t&)value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("int32") == 0) {
                int32_t value = item->text(GT::COL_FR_VALUE).toLong();
                ret = m_com->writeRAM32(axisInx, ofst, page, value);
    //            ret = m_com->readRAM32(axisInx, ofst, page, value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("Uint64") == 0) {
                uint64_t value = item->text(GT::COL_FR_VALUE).toULongLong();
                ret = m_com->writeRAM64(axisInx, ofst, page, value);
    //            ret = m_com->readRAM64(axisInx, ofst, page, (int64_t&)value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("int64") == 0) {
                int64_t value = item->text(GT::COL_FR_VALUE).toLongLong();
                ret = m_com->writeRAM64(axisInx, ofst, page, value);
    //            ret = m_com->readRAM64(axisInx, ofst, page, value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else if (itemType.compare("int16") == 0) {
                int16_t value = item->text(GT::COL_FR_VALUE).toShort();
                ret = m_com->writeRAM16(axisInx, ofst, page, value);
    //            ret = m_com->readRAM16(axisInx, ofst, page, value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            } else {
                uint16_t value = item->text(GT::COL_FR_VALUE).toUShort();
                ret = m_com->writeRAM16(axisInx, ofst, page, value);
    //            ret = m_com->readRAM16(axisInx, ofst, page, (int16_t&)value);
    //            item->setText(GT::COL_FR_VALUE, QString::number(value));
            }
            if (ret != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

quint64 LinkSocket::genCmdRead(const QString &cmdReadName, qint16 axisIndex, bool &isOk)
{
  return m_genCmd->read(cmdReadName,axisIndex,isOk);
}

bool LinkSocket::genCmdWrite(const QString &cmdWriteName, quint64 value, qint16 axisIndex)
{
  return m_genCmd->write(cmdWriteName,value,axisIndex);
}

qint16 LinkSocket::genReadErrorCode()
{
  return m_genCmd->readErrorCode();
}

bool LinkSocket::containsCmd(const QString &cmdName)
{
  return m_genCmd->containsCmd(cmdName);
}

void LinkSocket::setTryWriteCount(quint8 tryWriteCount)
{
  m_tryWriteCount = tryWriteCount;
}

ComDriver::ICom *LinkSocket::comObject() const
{
  return m_com;
}

bool LinkSocket::adjust(void (*processCallBack)(void *, short *), void *uiProcessBar)
{
  errcode_t err=0;
  err=m_com->open(processCallBack,uiProcessBar);
  m_com->close();
  qDebug()<<"adjust 1";
  if(err==0)
    return true;

  //先保存原来的com
  ComDriver::ICom *prevCom=m_com;
  ComDriver::ICom *newCom=NULL;

  if(m_com->iComType()==ComDriver::ICOM_TYPE_RNNET)
  {
    newCom=new PcDebug();
  }
  else if(m_com->iComType()==ComDriver::ICOM_TYPE_PCDEBUG)
  {
    newCom=new RnNet();
  }
  err=newCom->open(processCallBack,uiProcessBar);
  newCom->close();
  if(err==0)
  {
    //找到了对应的通信方式
    m_com=newCom;
    delete prevCom;
  }
  else
  {
    delete newCom;
  }

  m_genCmd->setICom(m_com);
  qDebug()<<"adjust end"<<QString::fromStdString(m_com->iComObjectName());

  return err==0;
}

bool LinkSocket::clearAlarm(quint16 axisInx)
{
  return 0==m_com->clearAlarm(axisInx);
}
