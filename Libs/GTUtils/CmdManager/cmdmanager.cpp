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

int CmdManager::getBaseAddress(const QString &key)
{
  int result = -1;
  QStringList list = key.split(".");
//  qDebug()<<"key = "<<list;
//  qDebug()<<"map "<<m_map.keys();
  if(!list.isEmpty())
  {
    QString first = list.at(0);
    if (m_map.contains(first)) {
      result = m_map.value(first);
      qDebug()<<"find value"<<first<<result;
    }
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
    value = data("ramPage", "gSevDrv", 0).toInt();
    m_map.insert("gSevDrv", value);
    value = data("ramPage", "gAuxFunc", 1).toInt();
    m_map.insert("gAuxFunc", value);
}

