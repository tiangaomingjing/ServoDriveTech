#ifndef SEVDEVICE_H
#define SEVDEVICE_H

#include <QObject>

namespace ComDriver {
class ICom;
}

class DeviceConfig;
class LinkSocket;
class ICtrBoard;
class IPwrBoard;
class IDspMap;
class SevDevicePrivate;

class SevDevice : public QObject
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(SevDevice)

public:
  explicit SevDevice(QObject *parent=0);
  ~SevDevice();
  bool init(const DeviceConfig *dConfig);
  void adjustSocket(ComDriver::ICom *com);
  QString typeName() const;
  QString modelName() const;
  QString versionName()const;
  quint32 pwrId() const ;
  quint32 ctrId() const;
  quint32 fpgaId() const ;
  quint8 axisNum() const;

signals:
  void initProgressInfo(int value,QString msg);
public slots:
private:
  SevDevicePrivate *d_ptr;
};

#endif // SEVDEVICE_H
