#include "devtextrwriter.h"
#include "Kernel/deviceconfig.h"
#include "pcdebug.h"
#include "rnnet.h"

DevTextRWriter::DevTextRWriter(QTreeWidget *idMapTree, QObject *parent):IDevReadWriter(idMapTree,parent)
{

}

QList<DeviceConfig *>DevTextRWriter::createConfig(bool &isOk)
{
  QList<DeviceConfig *> list;
  DeviceConfig *device=new DeviceConfig();
  list.append(device);
  isOk=true;
  return list;
}

bool DevTextRWriter::saveConfig(const DeviceConfig *config)
{
  return true;
}
