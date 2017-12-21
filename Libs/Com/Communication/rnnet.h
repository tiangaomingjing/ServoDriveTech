#ifndef RNNET_H
#define RNNET_H
#include "pcdebug.h"

COM_NAMESPACE_BEGIN

class RnNetPrivate;

class COMSHARED_EXPORT RnNet:public PcDebug
{
  Q_DECLARE_PRIVATE(RnNet)
public:
  explicit RnNet(const string &objectName="RnNet");
  virtual ~RnNet();

  errcode_t setRnStation(uint16_t rnstation);
  uint16_t currentRnStation() const;
  std::vector<uint8_t> broadcast();
};

COM_NAMESPACE_END
#endif // RNNET_H
