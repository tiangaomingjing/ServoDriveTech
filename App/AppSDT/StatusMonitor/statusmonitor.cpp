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
  m_devErrorStatusMap.clear();
  foreach (SevDevice *dev, m_sevDeviceList)
  {
    QVector<bool> errVec;
    for(int i =0;i<dev->axisNum();i++)
      errVec.append(false);
    m_devErrorStatusMap.insert(dev->devId(),errVec);
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

/**
 * @brief StatusMonitor::sysHasError
 * @return -1无报警
 */
int StatusMonitor::sysHasAlarmError()
{
  QMapIterator<int ,QVector<bool>> it(m_devErrorStatusMap);
  int dev = -1;
  while(it.hasNext())
  {
    it.next();
    for(int i=0;i<it.value().size();i++)
    {
      if(it.value().at(i) == false)
      {
        dev = it.key();
        break;
      }
      qDebug()<<"dev ="<<it.key()<<"axis = "<<i<<"error = "<<it.value().at(i);
    }
  }
  return dev;
}

void StatusMonitor::onMonitorTimeOut()
{
  //qDebug()<<"monitor timeout";
  bool online=true;
  foreach (SevDevice *dev, m_sevDeviceList)
  {
    online=dev->checkNetStatus();
    if(!online)
    {
      stopMonitor();
      emit netError(dev->devId());
      break;
    }
  }
}

void StatusMonitor::onAlarmError(quint16 devId, quint16 axisInx, bool hasError)
{
  if(m_devErrorStatusMap.contains(devId))
  {
    m_devErrorStatusMap[devId][axisInx] = hasError ;
  }
  emit alarmError(devId,axisInx,hasError);
  qDebug()<<"StatusMonitor emit alarm error";
}

