#ifndef SEVPWRBOARD_H
#define SEVPWRBOARD_H
#include "ipwrboard.h"
#include "PowerTreeManage/powertreemanage.h"

class SevPwrBoard:public IPwrBoard
{
  Q_OBJECT
public:
  explicit SevPwrBoard(SevDevicePrivate *sev,QObject *parent = 0);
  ~ SevPwrBoard();
  QList<QMap<QString, PowerBoardLimit> > *pwrLimitMapList();
  SamplingDataInfo pwrSamplingDataInfo();
private:
  PowerTreeManage *m_pTreeManage;
  QList<QMap<QString ,PowerBoardLimit>>m_powerLimitMapList;

};

#endif // SEVPWRBOARD_H
