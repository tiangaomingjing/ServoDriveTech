#include "linksocket.h"
#include "icom.h"


LinkSocket *LinkSocket::m_instance=NULL;
QMutex *LinkSocket::m_mutex=new QMutex;
LinkSocket *LinkSocket::instance(SevDevice *sev,ComDriver::ICom *com,QObject *parent)
{
  if(m_instance==NULL)
  {
    QMutexLocker locker(m_mutex);
    if(m_instance==NULL)
      m_instance=new LinkSocket(sev,com,parent);
  }
  return m_instance;
}

LinkSocket::LinkSocket(SevDevice *sev, ComDriver::ICom *com, QObject *parent) : QObject(parent),
  m_com(com),q_ptr(sev)
{

}
LinkSocket::~LinkSocket()
{

}
LinkSocket::LinkSocket(QObject *parent):QObject(parent)
{

}

void LinkSocket::connect(ComDriver::ICom *com)
{
  m_com=com;
}

QString LinkSocket::socketName()const
{
  return QString::fromStdString( m_com->iComObjectName());
}
quint8 LinkSocket::socketTypeId()const
{
  return quint8(m_com->iComType());
}
