#ifndef DEVTEXTRWRITER_H
#define DEVTEXTRWRITER_H
#include <QObject>
#include "idevreadwriter.h"

class DevTextRWriter:public IDevReadWriter
{
  Q_OBJECT
public:
  explicit DevTextRWriter(QTreeWidget *idMapTree,QObject *parent=0);
  virtual ~DevTextRWriter(){}
  //获取全局设备配置文件路径，得到信息
  QList<DeviceConfig *>createConfig(bool &isOk)override;
  bool saveConfig(const DeviceConfig *config)override;
};

#endif // DEVTEXTRWRITER_H
