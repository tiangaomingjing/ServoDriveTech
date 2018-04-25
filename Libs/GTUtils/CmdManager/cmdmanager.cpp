#include "cmdmanager.h"
#include "gtutils.h"

#include <QSettings>
#include <QDebug>

#define TABLE_INI "cmdMap.ini"

CmdManager::CmdManager(QObject *parent) : QObject(parent)
{
    m_tablePath = GTUtils::cmdPath() + TABLE_INI;
    iniMap();
}

int CmdManager::getValue(const QString &key)
{
    int result = -1;
    if (m_map.contains(key)) {
        result = m_map.value(key);
    }
    return result;
}

QVariant CmdManager::data(const QString &group, const QString &key, const QVariant &defaultValue)
{
    QSettings settings(m_tablePath ,QSettings::IniFormat);
    QVariant vd;
    settings.beginGroup(group);
    vd=settings.value(key,defaultValue);
    settings.endGroup();
    return vd;
}

void CmdManager::iniMap()
{
    int value;
    value = data("ramPage", "gSerDrv", 0).toInt();
    m_map.insert("gSerDrv", value);
    value = data("ramPage", "gAuxFunc", 0).toInt();
    m_map.insert("gAuxFunc", value);
}

