#ifndef IDEVREADWRITER_H
#define IDEVREADWRITER_H

#include <QObject>
#include <QMap>

class QTreeWidget;
class DeviceConfig;

namespace ComDriver {
  class ICom;
}

class IDevReadWriter:public QObject
{
  Q_OBJECT
public:
  explicit IDevReadWriter(QObject *parent=0);
  virtual ~IDevReadWriter(){}
  virtual QList<DeviceConfig *>createConfig(void (*processCallback)(void *pbar,short *value),void *processbar,bool &isOk)=0;
  virtual bool saveConfig(const QList<DeviceConfig *> &configList)=0;

signals:
  void sendDevProcessInfo(int value, const QString &msg);

protected:
  DeviceConfig *m_currentConfig;
  QMap<int ,QString>m_comTypeNameMap;

};

#endif // IDEVREADWRITER_H
