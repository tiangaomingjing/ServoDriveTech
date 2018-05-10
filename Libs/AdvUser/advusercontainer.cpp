#include "advusercontainer.h"
#include "iadvuser.h"

#include <QHash>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

QHash<QString, IAdvUser*> AdvUserContainer::m_advHash;
AdvUserContainer* AdvUserContainer::m_instance = NULL;

AdvUserContainer *AdvUserContainer::instance(QObject *parent)
{
    static QMutex mutex;
    if (!m_instance) {
        QMutexLocker locker(&mutex);
        if (!m_instance) {
            m_instance = new AdvUserContainer(parent);
        }
    }
    return m_instance;
}

AdvUserContainer::~AdvUserContainer()
{

}

void AdvUserContainer::addAdvUserItem(IAdvUser *adv)
{
    if (!m_advHash.contains(adv->name())) {
        m_advHash.insert(adv->name(), adv);
        m_advList.append(adv);
    } else {
        delete adv;
    }
}

IAdvUser *AdvUserContainer::advItem(const QString &advName)
{
    if (!m_advHash.contains(advName)) {
        return NULL;
    } else {
        return m_advHash.value(advName);
    }
}

QList<IAdvUser*> AdvUserContainer::advItems()
{
    return m_advList;
}

void AdvUserContainer::saveAdv()
{
    for (int i = 0; i < m_advList.length(); i++) {
        IAdvUser *adv = m_advList.at(i);
        adv->saveSettings();
    }
}

AdvUserContainer::AdvUserContainer(QObject *parent) : QObject(parent)
{

}

AdvUserContainer::AdvUserContainer(AdvUserContainer &oc)
{
    Q_UNUSED(oc);
}

