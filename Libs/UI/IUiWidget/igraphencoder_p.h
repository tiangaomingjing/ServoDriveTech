#ifndef IGRAPHBRAKE_P_H
#define IGRAPHBRAKE_P_H
#include "igraphencoder.h"
#include "igraph_p.h"
class IDataBinding ;
class IEncConfigItem;
class EncConfigManage;

class IUIWIDGETSHARED_EXPORT IGraphEncoderPrivate:public IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraphEncoder)
public:
  IGraphEncoderPrivate();
  virtual ~IGraphEncoderPrivate();
protected:

  IEncConfigItem *m_curEncConfigItem;
  EncConfigManage *m_encConfigManage;
  IDataBinding *m_iDataBinding;
};

#endif // IGRAPHBRAKE_P_H

