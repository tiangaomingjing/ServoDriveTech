#include "linksocket.h"
#include "icom.h"
#include "sevdeviceprivate_p.h"
#include "pcdebug.h"
#include "rnnet.h"

#include <QTreeWidgetItem>
#include <QDebug>

using namespace ComDriver;

LinkSocket::LinkSocket(SevDevicePrivate *sev, QObject *parent):QObject(parent),q_ptr(sev),m_isConnected(false),
  m_tryWriteCount(3)
{
  switch(sev->m_comType)
  {
  case ICOM_TYPE_PCDEBUG:
    m_com=new PcDebug(tr("PcDebug").toStdString());
    break;
  case ICOM_TYPE_RNNET:
  {
    RnNet *rnNet=new RnNet(tr("RnNet").toStdString());
    rnNet->setRnStation(sev->m_rnStationId);
    m_com=rnNet;
  }
    break;
  case ICOM_TYPE_SOCKET:
    break;
  case ICOM_TYPE_VIRTUAL:
    break;
  default:
    break;
  }
}

LinkSocket::~LinkSocket()
{

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

bool LinkSocket::readPageFlash(int axis,QTreeWidgetItem *item)
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
bool LinkSocket::writePageFlash(int axis,QTreeWidgetItem *item)
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
    wv=item->text(COL_PAGE_TREE_VALUE).toUShort();

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
    wv=item->text(COL_PAGE_TREE_VALUE).toShort();

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
    wv=item->text(COL_PAGE_TREE_VALUE).toUInt();

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
    wv=item->text(COL_PAGE_TREE_VALUE).toInt();

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
    wv=item->text(COL_PAGE_TREE_VALUE).toULongLong();

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
    wv=item->text(COL_PAGE_TREE_VALUE).toLongLong();

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
    wv=item->text(COL_PAGE_TREE_VALUE).toUShort();

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

void LinkSocket::setTryWriteCount(quint8 tryWriteCount)
{
  m_tryWriteCount = tryWriteCount;
}
