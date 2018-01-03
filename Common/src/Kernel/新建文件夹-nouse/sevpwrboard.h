#ifndef SEVPWRBOARD_H
#define SEVPWRBOARD_H
#include <QMap>
#include "ipwrboard.h"


class SevPwrBoard:public IPwrBoard
{
  Q_OBJECT
public:
  explicit SevPwrBoard(SevDevicePrivate *sev,QObject *parent = 0);
  ~ SevPwrBoard();
  QList<QMap<QString, PowerBoardLimit> > *pwrLimitMapList()Q_DECL_OVERRIDE;
  SamplingDataInfo pwrSamplingDataInfo()Q_DECL_OVERRIDE;
private:

};

#endif // SEVPWRBOARD_H
