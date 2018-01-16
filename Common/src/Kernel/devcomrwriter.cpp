#include "devcomrwriter.h"
#include "icom.h"
#include "pcdebug.h"
#include "rnnet.h"
#include "deviceconfig.h"
#include "deviceidhelper.h"

#include <QVector>
#include <QDebug>

using namespace ComDriver;
DevComRWriter::DevComRWriter(QObject *parent):IDevReadWriter(parent)
{

}

QList<DeviceConfig *>DevComRWriter::createConfig(void (*processCallback)(void *pbar,short *value),void *processbar,bool &isOk)
{
  QList<DeviceConfig *> list;
  ICom *com=new RnNet("rnnet");
  qDebug()<<"comtype"<<(int)com->iComType();
  errcode_t err=com->open(processCallback,processbar);
  isOk=true;
  if(err!=0)
  {
    com->close();
    delete com;
    com=new PcDebug("pcdebug");
    err=com->open(processCallback,processbar);
    if(err!=0)
    {
      com->close();
      delete com;
      isOk=false;
      return list;
    }
  }
  QString name;
  std::string str=com->iComObjectName();
  name=QString(str.c_str());
  qDebug()<<"com "<<name;

  if(com->iComType()==ICOM_TYPE_RNNET)
  {
    RnNet *rnNet=dynamic_cast<RnNet *>(com);
    std::vector<uint8_t> vtr=rnNet->broadcast();
    qDebug()<<"size"<<vtr.size();

    std::vector<uint8_t>::iterator it=vtr.begin();
    while(it!=vtr.end())
    {
      qDebug()<<(*it);
      ++it;
    }
    QVector<uint8_t> v;
    v=QVector<uint8_t>::fromStdVector(vtr);
    int i=0;
    foreach (uint8_t station, v)
    {
      rnNet->setRnStation(station);
      DeviceConfig *config=buildConfigFromCom(i,station,rnNet);
      qDebug()<<"DeviceConfig m_axisNum="<<config->m_axisNum;
      qDebug()<<"DeviceConfig m_pwrId="<<config->m_pwrId;
      qDebug()<<"DeviceConfig m_ctrId="<<config->m_ctrId;
      qDebug()<<"DeviceConfig m_comType="<<config->m_comType;
      qDebug()<<"DeviceConfig m_devId="<<config->m_devId;
      qDebug()<<"DeviceConfig m_fpgaId="<<config->m_fpgaId;
      qDebug()<<"DeviceConfig m_modeName="<<config->m_modeName;
      qDebug()<<"DeviceConfig m_typeName="<<config->m_typeName;
      qDebug()<<"DeviceConfig m_rnStationId="<<config->m_rnStationId;
      list.append(config);
      i++;
    }
  }
  else
  {
    DeviceConfig *config=buildConfigFromCom(0,-1,com);
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

DeviceConfig* DevComRWriter::buildConfigFromCom(quint8 devId, quint8 rnstation, ComDriver::ICom *com)
{
  DeviceConfig *config=new DeviceConfig;
  DeviceIdHelper idHelper(com);
  config->m_pwrId= idHelper.readPwrId();
  config->m_ctrId= idHelper.readCtrId();
  config->m_version=idHelper.readVersion();
  config->m_comType=com->iComType();
  config->m_axisNum=idHelper.axisNumFromIdMap();
  config->m_devId=devId;
  config->m_fpgaId=idHelper.readFpgaId();
  config->m_modeName=idHelper.modeNameFromIdMap();
  config->m_typeName=idHelper.typeNameFromIdMap();
  config->m_rnStationId=rnstation;
  return config;
}
void DevComRWriter::printfInfo(void *argv, short *v)
{
  int va=*v;
  printf("value=%d\n",va);
}
