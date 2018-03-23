#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphstatus.h"
#include "igraph_p.h"
#include "iuiwidget_global.h"
#include <QStringList>

class LedAlarm;
class QTimer;
class IUIWIDGETSHARED_EXPORT IGraphStatusPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphStatus)
public:
  IGraphStatusPrivate():
    m_ledFlag(NULL),
    m_timer(NULL)
  {

  }
  virtual ~IGraphStatusPrivate(){}
protected:
  LedAlarm *m_ledFlag;
  QList<LedAlarm*>m_ledAlarmList;
  QTimer *m_timer;
  QStringList m_sevStatusText;
  QStringList m_sevModeText;
  QStringList m_sevUsrModeText;
};

#endif // IGRAPHBRAKE_P_H

