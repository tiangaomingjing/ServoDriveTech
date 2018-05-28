#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphencoder.h"
#include "igraph_p.h"
#include "iuiwidget_global.h"
class IDataBinding ;
class IEncConfigItem;
class EncConfigManage;
class QTimer;

class IUIWIDGETSHARED_EXPORT IGraphEncoderPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphEncoder)
public:
  IGraphEncoderPrivate():
    m_curEncConfigItem(NULL),
    m_encConfigManage(NULL),
    m_iDataBinding(NULL),
    m_updateTimer(NULL),
    m_posOffset(1024),
    m_phaseDir(0)
  {

  }
  virtual ~IGraphEncoderPrivate(){}
protected:

  IEncConfigItem *m_curEncConfigItem;
  EncConfigManage *m_encConfigManage;
  IDataBinding *m_iDataBinding;
  QTimer*m_updateTimer;
  qint32 m_posOffset;
  qint16 m_phaseDir;
};

#endif // IGRAPHBRAKE_P_H

