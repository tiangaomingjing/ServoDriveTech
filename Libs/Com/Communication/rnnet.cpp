#include "rnnet.h"
#include "rnnet_p.h"
COM_USE_NAMESPACE

RnNetPrivate::RnNetPrivate():PcDebugPrivate()
{

}
RnNetPrivate::~RnNetPrivate()
{

}

RnNet::RnNet(const string &objectName):PcDebug(*new RnNetPrivate())
{
  Q_D(RnNet);
  d->m_objectName=objectName;
  d->m_comType=ICOM_TYPE_RNNET;
  d->m_rnStation=0xf0;
}
RnNet::~RnNet()
{

}

errcode_t RnNet::setRnStation(uint16_t rnstation)
{
  Q_D(RnNet);
  d->m_rnStation=rnstation;
  return 0;
}

uint16_t RnNet::currentRnStation() const
{
  Q_D(const RnNet);
  return d->m_rnStation;
}
