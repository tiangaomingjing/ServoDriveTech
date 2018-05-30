#include "imaxprmassociationhelper.h"
#include "gtutils.h"
#include "sevdevice.h"
#include "qttreemanager.h"
#include "sevdeviceprivate_p.h"
#include "icom.h"

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QDebug>
#include <QMessageBox>

#define PRM_IMAX_ASSOSIATION_NAME "PrmImaxAssosiation.xml"

typedef enum {
  ROW_AXIS_IMAX_INFO,
  ROW_AXIS_GAIN_INFO
}RowAxisIndex;

typedef enum {
  ROW_WRITE_FLASH_NAME,
  ROW_WRITE_FLASH_TYPE,
  ROW_WRITE_FLASH_OFFSET
}RowWriteFlashInfo;

typedef enum {
  ROW_GAIN_IX_WRITEFLASH,
  ROW_GAIN_IX_SAMPLINE_TYPE,
}RowGainIx;
typedef enum {
  COL_IMAX_MOTOR_NAME,
  COL_IMAX_MOTOR_PRM,
  COL_IMAX_MOTOR_INTRODUCTION
}ColImaxMotor;


ImaxPrmAssociationHelper::ImaxPrmAssociationHelper(SevDevice *sev, QObject *parent) : QObject(parent),
  m_sev(sev)
{
  QString prmFuncExtentionPath = GTUtils::sysPath() + \
      sev->typeName()+"/"+\
      sev->modelName()+"/"+\
      sev->versionName() + "/" +\
      "prm_assosiation/"+PRM_IMAX_ASSOSIATION_NAME;

  m_motorTree = QtTreeManager::createTreeWidgetFromXmlFile(prmFuncExtentionPath);

}

ImaxPrmAssociationHelper::~ImaxPrmAssociationHelper()
{
  m_motorTree->clear();

  delete m_motorTree ;
}

double ImaxPrmAssociationHelper::readImaxValueFromDevice(quint16 axisInx, QString type, quint16 imaxOffset)
{
  double imaxValue = 1;
  if(type == "Uint16")
  {
    ComDriver::int16_t imax = 100;
    m_sev->socketCom()->readFLASH16(axisInx,imaxOffset,0,imax);
    imaxValue = imax;
  }
  else if(type == "int16")
  {
    qint16 imax = 100;
    m_sev->socketCom()->readFLASH16(axisInx,imaxOffset,0,imax);
    imaxValue = imax;
  }
  else if(type == "Uint32")
  {
    ComDriver::int32_t imax = 100;
    m_sev->socketCom()->readFLASH32(axisInx,imaxOffset,0,imax);
    imaxValue = imax;
  }
  else if(type == "int32")
  {
    ComDriver::int32_t imax = 100;
    m_sev->socketCom()->readFLASH32(axisInx,imaxOffset,0,imax);
    imaxValue = imax;
  }
  else
  {
    ComDriver::int16_t imax = 100;
    m_sev->socketCom()->readFLASH16(axisInx,imaxOffset,0,imax);
    imaxValue = imax;
  }
  return imaxValue;
}

bool ImaxPrmAssociationHelper::writeIxDataToFlash(quint16 axisInx, QString type, quint16 offst,quint64 value)
{
  if(type == "Uint16")
  {
    quint16 v = value;
    return m_sev->socketCom()->writeFLASH16(axisInx,offst,0,v);
  }
  else if(type == "int16")
  {
    qint16 v = value;
    return m_sev->socketCom()->writeFLASH16(axisInx,offst,0,v);
  }
  else if(type == "Uint32")
  {
    quint32 v = value;
    return m_sev->socketCom()->writeFLASH32(axisInx,offst,0,v);
  }
  else if(type == "int32")
  {
    qint32 v = value;
    return m_sev->socketCom()->writeFLASH32(axisInx,offst,0,v);
  }
  else
  {
    quint16 v = value;
    return m_sev->socketCom()->writeFLASH16(axisInx,offst,0,v);
  }

}

bool ImaxPrmAssociationHelper::active(quint16 axisInx)
{
  //gain =shunt (64424512)*dspversionfactor (2)/电阻值rValue
  //k = gain / imaxValue ;
  //shunt dspversionfactor 的数据来自PrmFuncExtention.xml Motor  每个版本中dspversionfactor可能不一样
  //rValue 的数据来自刘超文功率板的PB.xml采样电阻值
  //最后计算的ka kb kc 要写到PrmFuncExtention.xml记录中 ia ib ic
  SamplingData data = m_sev->d_ptr->m_pwrBoard->pwrSamplingDataAt(axisInx);

  QTreeWidgetItem *axisItem = m_motorTree->topLevelItem(0)->child(axisInx);
  QTreeWidgetItem *imaxItem = axisItem->child(ROW_AXIS_IMAX_INFO);
  QTreeWidgetItem *gainItem = axisItem->child(ROW_AXIS_GAIN_INFO);

  bool ret = true;
  for(int i=0;i<gainItem->childCount();i++)
  {
    QTreeWidgetItem *itemIx = gainItem->child(i);
    QTreeWidgetItem *itemSamplingType = itemIx->child(ROW_GAIN_IX_SAMPLINE_TYPE)->child(data.m_type);
    QTreeWidgetItem *itemWriteFlash = itemIx->child(ROW_GAIN_IX_WRITEFLASH);
    double gain = 0 ;
    quint16 imaxOffset = imaxItem->child(ROW_WRITE_FLASH_OFFSET)->text(COL_IMAX_MOTOR_PRM).toUShort();
    QString type = imaxItem->child(ROW_WRITE_FLASH_TYPE)->text(COL_IMAX_MOTOR_PRM);
    double imaxValue = readImaxValueFromDevice(axisInx, type, imaxOffset);

    double shunt = itemSamplingType->text(COL_IMAX_MOTOR_PRM).toDouble();
    double factor = itemSamplingType->child(0)->text(COL_IMAX_MOTOR_PRM).toDouble();
    gain = shunt * factor / data.m_value;


    double k = gain /imaxValue;
    if(k>32767)
    {
      k = 32767;
      QMessageBox::information(0,tr("warning"),tr("Imax is too small !"));
    }

    qDebug()<<"Ix : "<<itemIx->text(0)<<"gain = "<<gain<<"res value = "<<data.m_value<<"res type = "<<data.m_type<<"Imax = "<<imaxValue<<"k = "<<k;

    QString flashType = itemWriteFlash->child(ROW_WRITE_FLASH_TYPE)->text(COL_IMAX_MOTOR_PRM);
    quint16 flashOffset = itemWriteFlash->child(ROW_WRITE_FLASH_OFFSET)->text(COL_IMAX_MOTOR_PRM).toUShort();
    bool writeOk = writeIxDataToFlash(axisInx,flashType,flashOffset,(quint64)k);
    if(!writeOk)
    {
      if(false==writeIxDataToFlash(axisInx,flashType,flashOffset,(quint64)k))
         ret = false;
    }
  }
  return ret;

}

