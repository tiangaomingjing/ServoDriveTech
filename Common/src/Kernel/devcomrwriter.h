#ifndef DEVCOMRWRITER_H
#define DEVCOMRWRITER_H

#include "idevreadwriter.h"

class DevComRWriter:public IDevReadWriter
{
  Q_OBJECT
public:
  explicit DevComRWriter(QTreeWidget *idMapTree, QObject *parent=0);
  QList<DeviceConfig *>createConfig(bool &isOk)override;
  bool saveConfig(const DeviceConfig *config)override;
};

#endif // DEVCOMRWRITER_H
