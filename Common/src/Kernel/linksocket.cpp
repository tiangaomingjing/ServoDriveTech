#include "linksocket.h"

LinkSocket::LinkSocket(SevDevice *sev, ComDriver::ICom *com, QObject *parent) : QObject(parent),
  m_com(com),q_ptr(sev)
{

}
LinkSocket::~LinkSocket()
{

}

void LinkSocket::connect(ComDriver::ICom *com)
{
  m_com=com;
}
