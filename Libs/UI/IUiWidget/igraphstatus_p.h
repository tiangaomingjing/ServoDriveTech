#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphstatus.h"
#include "igraph_p.h"
class LedAlarm;
class IUIWIDGETSHARED_EXPORT IGraphStatusPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphStatus)
public:
  IGraphStatusPrivate();
  virtual ~IGraphStatusPrivate();
protected:
  LedAlarm *m_ledFlag;
  QList<LedAlarm*>m_ledAlarmList;
};

#endif // IGRAPHBRAKE_P_H

