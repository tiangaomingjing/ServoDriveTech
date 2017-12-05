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
  typedef enum{
    COL_NAME,
    COL_PRM,
    COL_ID
  }ConfigColumnInx;
  explicit IDevReadWriter(QObject *parent=0);
  virtual ~IDevReadWriter(){}
  virtual QList<DeviceConfig *>createConfig(bool &isOk)=0;
  virtual bool saveConfig(const DeviceConfig *config)=0;
protected:
  bool createIdMapTree(const QString &fileName);
protected:
  QTreeWidget *m_idMapTree;
  DeviceConfig *m_currentConfig;
};

#endif // IDEVREADWRITER_H
