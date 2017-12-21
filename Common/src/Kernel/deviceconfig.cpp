#include "deviceconfig.h"
#include <QDebug>

DeviceConfig::DeviceConfig(QObject *parent) : QObject(parent)
{

}

DeviceConfig::~DeviceConfig()
{
  qDebug()<<"DeviceConfig-->destruct";
}

bool DeviceConfig::isEqual(const DeviceConfig &devConfig)
{
  qDebug()<<"prm devconfig:"<<tr("pwrid=%1,ctrid=%2,comtype=%3,version=%4,stationid=%5").arg(devConfig.m_pwrId)\
            .arg(devConfig.m_ctrId).arg(devConfig.m_comType).arg(devConfig.m_version).arg(devConfig.m_rnStationId);
  qDebug()<<"target devconfig:"<<tr("pwrid=%1,ctrid=%2,comtype=%3,version=%4,stationid=%5").arg(m_pwrId)\
            .arg(m_ctrId).arg(m_comType).arg(m_version).arg(m_rnStationId);
  return (m_pwrId==devConfig.m_pwrId)&&\
         (m_ctrId==devConfig.m_ctrId)&&\
      (m_comType==devConfig.m_comType)&&\
      (m_version==devConfig.m_version)&&\
      (m_rnStationId==devConfig.m_rnStationId);
}
