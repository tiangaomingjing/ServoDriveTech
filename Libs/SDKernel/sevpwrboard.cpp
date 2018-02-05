#include "sevpwrboard.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "sevdeviceprivate_p.h"
#include "ipwrboard.h"
#include "deviceconfig.h"

#include <QDebug>
#include <QTreeWidget>

SevPwrBoard::SevPwrBoard(SevDevicePrivate *sev, QObject *parent):IPwrBoard(sev,parent)
{

//    bool isOk;
//    PowerTreeManage *pwrTreeManager = new PowerTreeManage(sev->m_devConfig->m_devId);
//    pwrTreeManager->updatePowerLimitMapList(sev->m_devConfig->m_version, m_powerLimitMapList);
//    m_samplingDataInfo = pwrTreeManager->samplingDataInfo(&isOk);
//    delete pwrTreeManager;
}

SevPwrBoard::~SevPwrBoard()
{
  qDebug()<<"SevPwrBoard-->destruct";
}
QList<QMap<QString ,PowerBoardLimit>>* SevPwrBoard::pwrLimitMapList()
{
  return &m_powerLimitMapList;
}

SamplingDataInfo SevPwrBoard::pwrSamplingDataInfo()
{
  return m_samplingDataInfo;
}
