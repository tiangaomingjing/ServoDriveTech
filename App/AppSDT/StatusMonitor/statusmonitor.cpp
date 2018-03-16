#include "statusmonitor.h"
#include "sevdevice.h"

#include <QTimer>
#include <QDebug>

StatusMonitor::StatusMonitor(QObject *parent) : QObject(parent),
  m_timer(new QTimer(this))
{
  connect(m_timer,SIGNAL(timeout()),this,SLOT(onMonitorTimeOut()));
}

StatusMonitor::~StatusMonitor()
{

}

void StatusMonitor::setMonitorDeviceList(QList<SevDevice *> devList)
{
  bool isOpen=m_timer->isActive();

  if(isOpen)
    m_timer->stop();

  m_sevDeviceList=devList;
  foreach (SevDevice *dev, m_sevDeviceList)
  {
    connect(dev,SIGNAL(alarmError(quint16,quint16,bool)),this,SIGNAL(alarmError(quint16,quint16,bool)));
  }

  if(isOpen)
    m_timer->start();
}

void StatusMonitor::startMonitor(quint16 ms)
{
  m_timer->setInterval(ms);
  m_timer->start();
}

void StatusMonitor::stopMonitor()
{
  m_timer->stop();
}

void StatusMonitor::onMonitorTimeOut()
{
  qDebug()<<"monitor timeout";
  bool offline=true;
  foreach (SevDevice *dev, m_sevDeviceList)
  {
    offline=dev->checkNetStatus();
    if(!offline)
    {
      emit netError(dev->devId());
      stopMonitor();
      break;
    }
  }
}

void StatusMonitor::onAlarmError(quint16 devId, quint16 axisInx, bool hasError)
{
  emit alarmError(devId,axisInx,hasError);
  qDebug()<<"StatusMonitor emit alarm error";
}

