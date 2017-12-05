#include "sevpwrboard.h"

SevPwrBoard::SevPwrBoard(SevDevicePrivate *sev, QObject *parent):IPwrBoard(sev,parent)
{
//  m_pTreeManage=new PowerTreeManage();
}

SevPwrBoard::~SevPwrBoard()
{
  delete m_pTreeManage;
}
QList<QMap<QString ,PowerBoardLimit>>* SevPwrBoard::pwrLimitMapList()
{
  m_powerLimitMapList.clear();
  return &m_powerLimitMapList;
}

SamplingDataInfo SevPwrBoard::pwrSamplingDataInfo()
{
  SamplingDataInfo sInfo;
  return sInfo;
}
