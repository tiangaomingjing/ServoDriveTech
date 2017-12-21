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
  printf("net object name =%s\n",objectName.c_str());
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
std::vector<uint8_t> RnNet::broadcast()
{
  std::vector<uint8_t> vtr;
  vtr.push_back(0xf0);
//  vtr.push_back(0xf1);//测试得到多个站信息
  return vtr;
}
