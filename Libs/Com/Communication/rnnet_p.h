#ifndef RNNET_P_H
#define RNNET_P_H
#include "pcdebug_p.h"
COM_NAMESPACE_BEGIN

class RnNetPrivate:public PcDebugPrivate
{
  Q_DECLARE_PUBLIC(RnNet)
public:
  RnNetPrivate();
  virtual ~RnNetPrivate();
  uint16_t m_rnStation;
};
COM_NAMESPACE_END

#endif // RNNET_P_H

