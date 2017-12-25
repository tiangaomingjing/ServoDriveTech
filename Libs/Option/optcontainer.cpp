#include "optcontainer.h"
#include "iopt.h"

#include <QHash>
#include <QMutex>
#include <QMutexLocker>
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
void OptContainer::addOptItem(IOpt*opt)
{
  if(!m_optHash.contains(opt->name()))
      m_optHash.insert(opt->name(),opt);
}

IOpt* OptContainer::optItem(const QString &optName)
{
  if(!m_optHash.contains(optName))
    return NULL;
  return m_optHash.value(optName);
}
void OptContainer::saveOpt()
{

}
