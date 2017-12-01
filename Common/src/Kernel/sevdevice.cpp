#include "sevdevice.h"
#include "linksocket.h"
#include "sdtglobaldef.h"
#include "deviceconfig.h"

SevDevice::SevDevice(const DeviceConfig *dConfig, QObject *parent):QObject(parent)
{

}
void SevDevice::adjustSocket(ComDriver::ICom *com)
{
  m_socket->connect(com);
}
