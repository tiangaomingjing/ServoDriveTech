#ifndef DEVCOMRWRITER_H
#define DEVCOMRWRITER_H

#include "idevreadwriter.h"

class DevComRWriter:public IDevReadWriter
{
  Q_OBJECT
public:
  explicit DevComRWriter( QObject *parent=0);
  QList<DeviceConfig *>createConfig(void (*processCallback)(void *pbar,short *value),void *processbar,bool &isOk)override;
  bool saveConfig(const DeviceConfig *config)override;

private:
  DeviceConfig* buildConfigFromCom(quint8 devId, quint8 rnstation, ComDriver::ICom *com);
  static void printfInfo(void *argv, short *v);
};

#endif // DEVCOMRWRITER_H
