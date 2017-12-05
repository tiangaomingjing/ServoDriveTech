#include "devcomrwriter.h"

DevComRWriter::DevComRWriter(QObject *parent):IDevReadWriter(parent)
{

}

QList<DeviceConfig *>DevComRWriter::createConfig(bool &isOk)
{
  QList<DeviceConfig *> list;
  return list;
}

bool DevComRWriter::saveConfig(const DeviceConfig *config)
{
  return true;
}
