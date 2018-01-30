#include "deviceidhelper.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "icom.h"


#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QDebug>
#define IDMAP_FILENAME "IdMap.ui"
#define IDMAP_FILENAME_COPY "IdMap_copy.ui"
#define PWR_BASE_ADDR 64
#define CTR_BASE_ADDR 128
using namespace ComDriver;
DeviceIdHelper::DeviceIdHelper(ComDriver::ICom *com, QObject *parent) : QObject(parent),m_com(com),
  m_pwrId(21000509),
  m_ctrId(0),
  m_fpgaId(0),
  m_axisNum(4),
  m_typeName("SD4x"),
  m_modeName("SD41")
{

}
DeviceIdHelper::~DeviceIdHelper()
{

}

quint32 DeviceIdHelper::readPwrId()
{
  //需要从硬件读取
//  quint32 id=21000509;//test for SD42
//  m_com->readEEPROM();//从硬件读取ID
  //m_pwrId=21000541;//test for SD61
  uint16_t ofst = 1 + PWR_BASE_ADDR;
  uint16_t num = 4;
  uint8_t value[4];
  uint8_t cs = 0;
  m_com->readEEPROM(ofst, value, num, cs);
  int id = 0;
  for (int i = 0; i < num; i++) {
      id = id + (value[i] << (i * 8));
  }
  m_pwrId = id;

  QString idMapPath=GTUtils::databasePath()+IDMAP_FILENAME;
  QTreeWidget *idMapTree=QtTreeManager::createTreeWidgetFromXmlFile(idMapPath);

  {
    QTreeWidgetItem *item;
    QTreeWidgetItemIterator it(idMapTree);
    while(*it)
    {
      item=*it;
      quint32 id=item->text(COL_IDMAP_ID).toUInt();
      if(id==m_pwrId)
      {
        m_typeName=item->text(COL_IDMAP_TYPE);
        m_modeName=item->text(COL_IDMAP_MODE);
        m_axisNum=item->text(COL_IDMAP_AXISNUM).toUInt();
        qDebug()<<tr("typeName=%1,modeName=%2,axisNum=%3").arg(m_typeName).arg(m_modeName).arg(m_axisNum);
        break;
      }
      it++;
    }
  }
  delete idMapTree;
  return m_pwrId;
}

quint32 DeviceIdHelper::readCtrId()
{
  //需要从硬件读取
    uint16_t ofst = 1 + CTR_BASE_ADDR;
    uint16_t num = 4;
    uint8_t value[4];
    uint8_t cs = 1;
    qDebug()<<"ofst"<<ofst;
    m_com->readEEPROM(ofst, value, num, cs);
    qDebug()<<"value[0]"<<value[0];
    int id = 0;
    for (int i = 0; i < num; i++) {
        id = id + (value[i] << (i * 8));
    }
    m_ctrId = id;
  return m_ctrId;
}
quint32 DeviceIdHelper::readFpgaId()
{
  //需要从硬件读取
    uint8_t fpgaInx = 0;
    uint16_t version;
    m_com->readFPGAVersion(fpgaInx, version);
    m_fpgaId = version;
  return m_fpgaId;
}

QString DeviceIdHelper::readVersion()
{
  //需要从硬件读取
    uint8_t dspInx = 0;
    uint16_t version;
    m_com->readDSPVersion(dspInx, version);
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


