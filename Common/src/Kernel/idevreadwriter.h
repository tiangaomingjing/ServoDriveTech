#ifndef IDEVREADWRITER_H
#define IDEVREADWRITER_H

#include <QObject>

class QTreeWidget;
class DeviceConfig;

namespace ComDriver {
  class ICom;
}

class IDevReadWriter:public QObject
{
  Q_OBJECT
public:
  explicit IDevReadWriter(QTreeWidget *idMapTree,QObject *parent=0):QObject(parent),m_idMapTree(idMapTree){}
  virtual ~IDevReadWriter(){}
  virtual QList<DeviceConfig *>createConfig(bool &isOk)=0;
  virtual bool saveConfig(const DeviceConfig *config)=0;
protected:
  QTreeWidget *m_idMapTree;
  DeviceConfig *m_config;
};

#endif // IDEVREADWRITER_H
