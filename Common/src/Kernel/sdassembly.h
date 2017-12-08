#ifndef SDASSEMBLY_H
#define SDASSEMBLY_H

#include <QObject>

class GlobalConfig;
class SevDevice;
class IUiControler;
class DeviceConfig;

class SdAssembly : public QObject
{
  Q_OBJECT
public:
  explicit SdAssembly(QObject *parent=0);
  ~SdAssembly();

  bool init(const DeviceConfig *dConfig,GlobalConfig *gConfig);

signals:
  void initProgressInfo(int value,QString msg);
public slots:
private:
  SevDevice *m_device;
  IUiControler *m_uiControler;
};

#endif // SDASSEMBLY_H
