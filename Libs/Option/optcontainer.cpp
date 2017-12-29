#include "optcontainer.h"
#include "iopt.h"

#include <QHash>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
QHash<QString,IOpt*>OptContainer::m_optHash;
OptContainer* OptContainer::m_instance=NULL;

OptContainer *OptContainer::instance(QObject *parent)
{
  static QMutex mutex;
  if(!m_instance)
  {
    QMutexLocker locker(&mutex);
    if(!m_instance)
    {
      m_instance=new OptContainer(parent);
      qDebug()<<"----new optcontainer----";
    }
  }
  return m_instance;
}

OptContainer::OptContainer(QObject *parent):QObject(parent)
{
}
OptContainer::~OptContainer()
{

}
OptContainer::OptContainer(OptContainer &oc)
{
  Q_UNUSED(oc);
}

void OptContainer::addOptItem(IOpt*opt)
{
  if(!m_optHash.contains(opt->name()))
  {
      m_optHash.insert(opt->name(),opt);
      m_optList.append(opt);
  }
}

IOpt* OptContainer::optItem(const QString &optName)
{
  if(!m_optHash.contains(optName))
    return NULL;
  return m_optHash.value(optName);
}
//返回的m_optHash.values() items排列顺序是随机的,所以加多一个QList存储
QList<IOpt*> OptContainer::optItems()
{
//  return m_optHash.values();
  return m_optList;
}

void OptContainer::saveOpt()
{
  foreach (IOpt *opt, m_optList)
  {
    opt->saveOptToFile();
    qDebug()<<opt->name()<<"save opt file";
  }
}
