#include "sevdevice.h"
#include "linksocket.h"
#include "sdtglobaldef.h"

SevDevice::SevDevice(ComDriver::ICom *com, const GT::DeviceConfig *dConfig, QObject *parent):QObject(parent),
  m_socket(new LinkSocket(this,com)),m_config(dConfig)
{

}
void SevDevice::adjustSocket(ComDriver::ICom *com)
{
  m_socket->connect(com);
}
