#ifndef IPWRBOARD_H
#define IPWRBOARD_H

#include <QObject>
#include "PowerTreeManage/powertreemanage.h"

class SevDevicePrivate;
class IPwrBoard : public QObject
{
  Q_OBJECT
public:
  explicit IPwrBoard(SevDevicePrivate *sev,QObject *parent = 0);
  virtual ~IPwrBoard();

  virtual QList<QMap<QString, PowerBoardLimit> > *pwrLimitMapList()=0;
  virtual SamplingDataInfo pwrSamplingDataInfo()=0;

signals:

public slots:

protected:
  SevDevicePrivate *q_ptr;
  QList<QMap<QString ,PowerBoardLimit>>m_powerLimitMapList;
  SamplingDataInfo m_samplingDataInfo;
};

#endif // IPWRBOARD_H
