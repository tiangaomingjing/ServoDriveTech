#include "deviceidhelper.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "icom.h"
#include "sdtglobaldef.h"


#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QDebug>
#define IDMAP_FILENAME "IdMap_Power.ui"
#define PWR_BASE_ADDR 128
#define PWR_ID_OFFSET 7
#define CTR_BASE_ADDR 128
#define CTR_ID_OFFSET 7

#define TEST_READ_VERSION 0

using namespace ComDriver;
DeviceIdHelper::DeviceIdHelper(QObject *parent):QObject(parent),
  m_com(NULL),
  m_pwrId(21000509),
  m_ctrId(0),
  m_fpgaId(0),
  m_axisNum(4),
  m_typeName("SD4x"),
  m_modeName("SD42"),
  m_hasPwrId(true)
{

}

DeviceIdHelper::DeviceIdHelper(ComDriver::ICom *com, QObject *parent) : QObject(parent),m_com(com),
  m_pwrId(21000509),
  m_ctrId(0),
  m_fpgaId(0),
  m_axisNum(4),
  m_typeName("SD4x"),
  m_modeName("SD42"),
  m_hasPwrId(true)
{

}
DeviceIdHelper::~DeviceIdHelper()
{

}
void DeviceIdHelper::setCom(ComDriver::ICom *com)
{
  m_com=com;
}

quint32 DeviceIdHelper::readPwrId(bool &isOk)
{
  //需要从硬件读取
//  quint32 id=21000509;//test for SD42
//  m_com->readEEPROM();//从硬件读取ID
  //m_pwrId=21000541;//test for SD61
  uint16_t ofst = PWR_ID_OFFSET + PWR_BASE_ADDR;
  uint16_t num = 4;
  uint8_t value[4];
  uint8_t cs = 0;
  errcode_t err=0;
  err=m_com->readEEPROM(ofst, value, num, cs);

  if(err!=0)
  {
    m_pwrId=0;
    isOk=false;
    return m_pwrId;
  }

  int id = 0;
  for (int i = 0; i < num; i++) {
      id = id + (value[i] << (i * 8));
  }
  m_pwrId = id;

  QString idMapPath=GTUtils::databasePath()+"Board/PB/"+IDMAP_FILENAME;
  QTreeWidget *idMapTree=QtTreeManager::createTreeWidgetFromXmlFile(idMapPath);
  bool findId=false;
  {
    QTreeWidgetItem *item;
    QTreeWidgetItemIterator it(idMapTree);
    while(*it)
    {
      item=*it;
      quint32 id=item->text(GT::COL_IDMAP_ID).toUInt();
      if(id==m_pwrId)
      {
        findId=true;
        m_hasPwrId=true;
        m_typeName=item->text(GT::COL_IDMAP_TYPE);
        m_modeName=item->text(GT::COL_IDMAP_MODE);
        m_axisNum=item->text(GT::COL_IDMAP_AXISNUM).toUInt();
        qDebug()<<tr("typeName=%1,modeName=%2,axisNum=%3").arg(m_typeName).arg(m_modeName).arg(m_axisNum);
        break;
      }
      it++;
    }
  }
  if(findId==false)
  {
    //NEED TO REWRITE
    //在IdMap_Power.ui文件中找不到这个ID，说明固件是新的，而调试软件是老版的，或是升级调试软件

    //从EPROM重构自己
    //重构成功，isOk=true else isOk=false

    m_typeName="NULL";
    m_modeName="NULL";
    m_axisNum=0;
    m_hasPwrId=false;
    isOk=false;
  }
  delete idMapTree;


  return m_pwrId;
}

quint32 DeviceIdHelper::readCtrId(bool &isOk)
{
  //需要从硬件读取
  uint16_t ofst = CTR_ID_OFFSET + CTR_BASE_ADDR;
  uint16_t num = 4;
  uint8_t value[4];
  uint8_t cs = 1;
  errcode_t err=0;
//  qDebug()<<"ofst"<<ofst;

  err=m_com->readEEPROM(ofst, value, num, cs);
  if(err!=0)
  {
    isOk=false;
    m_ctrId=0;
    return m_ctrId;
  }
  qDebug()<<"value[0]"<<value[0];
  int id = 0;
  for (int i = 0; i < num; i++) {
      id = id + (value[i] << (i * 8));
  }
  m_ctrId = id;

  //如在ctrId在id_CtlMap中找不到，说明调试软件是老的，模块是新的
  //从EPROM重构自己

  //重构成功，isOk=true else isOk=false

  return m_ctrId;
}
quint32 DeviceIdHelper::readFpgaId(bool &isOk)
{
  //需要从硬件读取
  uint8_t fpgaInx = 0;
  uint16_t version;
  errcode_t err=0;
  err=m_com->readFPGAVersion(fpgaInx, version);
  if(err!=0)
  {
    isOk=false;
    m_fpgaId=0;
    return m_fpgaId;
  }
  m_fpgaId = version;
  return m_fpgaId;
}

bool DeviceIdHelper::readFpgaDate(quint16 &year, quint16 &day)
{
  //需要从硬件读取
  uint8_t fpgaInx = 0;
  errcode_t err=0;
  err=m_com->readFPGAYearDay(fpgaInx,year,day);
  return err==0;
}

QString DeviceIdHelper::readVersion(bool &isOk)
{
#if TEST_READ_VERSION
    isOk=false;
    return "V0";
#endif
  //需要从硬件读取
    uint8_t dspInx = 0;
    uint16_t version;
    errcode_t err=0;
    err=m_com->readDSPVersion(dspInx, version);
    if(err!=0)
    {
      isOk=false;
      return "V0";
    }
    QString result = "V" + QString::number(version, 10);
    return result;
}

QString DeviceIdHelper::modeNameFromIdMap()
{
//  return "SD42";
//  return "SD61";
  return m_modeName;
}

QString DeviceIdHelper::typeNameFromIdMap()
{
//  return "SD4x";
//  return "SD6x";
  return m_typeName;
}
quint8 DeviceIdHelper::axisNumFromIdMap()
{
//  return 4;
//  return 6;
  return m_axisNum;
}

bool DeviceIdHelper::databaseHasPwrId() const
{
  return m_hasPwrId;
}


