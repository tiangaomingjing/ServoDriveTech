#include "devcomrwriter.h"

DevComRWriter::DevComRWriter(QTreeWidget *idMapTree, QObject *parent):IDevReadWriter(idMapTree,parent)
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
