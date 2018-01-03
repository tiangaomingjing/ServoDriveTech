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
class QTreeWidgetItem;
class QTreeWidget;

class SevDevice : public QObject
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(SevDevice)

public:
  explicit SevDevice(QObject *parent=0);
  ~SevDevice();
  bool init(const DeviceConfig *dConfig);

  void adjustSocket(ComDriver::ICom *com);
  bool enableConnection(void (*processCallBack)(void *argv, short *value), void *uiProcessBar);
  void disableConnection();

  QString typeName() const;
  QString modelName() const;
  QString versionName()const;
  quint32 pwrId() const ;
  quint32 ctrId() const;
  quint32 fpgaId() const ;
  quint8 axisNum() const;
  QTreeWidgetItem* targetTree() const;
  QTreeWidget *axisTreeSource(int axis,int page) const;
  QTreeWidget *globalTreeSource(int page) const;

signals:
  void initProgressInfo(int value,QString msg);
public slots:
  void onReadPageFlash(int axis,QTreeWidget *tree);
  void onWritePageFlash(int axis,QTreeWidget *tree);
private:
  SevDevicePrivate *d_ptr;
};

#endif // SEVDEVICE_H
