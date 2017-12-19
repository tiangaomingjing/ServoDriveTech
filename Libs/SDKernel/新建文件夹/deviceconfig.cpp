#include "deviceconfig.h"
#include <QDebug>

DeviceConfig::DeviceConfig(QObject *parent) : QObject(parent)
{

}

DeviceConfig::~DeviceConfig()
{
  qDebug()<<"DeviceConfig-->destruct";
}
