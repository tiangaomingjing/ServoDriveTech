#ifndef SEVDEVICE_H
#define SEVDEVICE_H

#include <QObject>
#include "sdkernel_global.h"
#include "sevpwrboard.h"

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

class SDKERNELSHARED_EXPORT SevDevice : public QObject
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(SevDevice)

public:
  explicit SevDevice(QObject *parent=0);
  ~SevDevice();
  bool init(const DeviceConfig *dConfig);

  bool adjustSocket(void (*processCallBack)(void *argv, short *value), void *uiProcessBar);
  ComDriver::ICom *socketCom() const;

  bool enableConnection(void (*processCallBack)(void *argv, short *value), void *uiProcessBar);
  void disableConnection();
  bool isConnecting() const;

  bool containsCmd(const QString &cmdKey);

  quint64 genCmdRead(const QString &cmdReadName,qint16 axisIndex,bool &isOk);
  bool genCmdWrite(const QString &cmdWriteName,quint64 value,qint16 axisIndex);

  bool readGenItemRAM(quint16 axisInx,QTreeWidgetItem *item);
  bool writeGenItemRAM(quint16 axisInx,QTreeWidgetItem *item);
  bool readGenPageRAM(quint16 axisInx,QTreeWidget *pageTree);
  bool writeGenPageRAM(quint16 axisInx,QTreeWidget *pageTree);

  bool writeItemFlash(quint16 axisInx,QTreeWidgetItem *item);
  bool readItemFlash(quint16 axisInx,QTreeWidgetItem *item);

  bool clearAlarm(quint16 axisInx);

  QString aliasName() const;
  QString typeName() const;
  QString modelName() const;
  QString versionName()const;

  quint32 devId() const;
  quint32 pwrId() const ;
  quint32 ctrId() const;
  quint32 fpgaId() const ;
  quint8 axisNum() const;
  DeviceConfig *deviceConfig() const;
  QTreeWidgetItem* targetTree() const;
  QTreeWidget *axisTreeSource(int axis,int page) const;
  QTreeWidget *globalTreeSource(int page) const;

  void setVersionAttributeActive();

  bool checkNetStatus();

  QString filePath() const;

  Q_INVOKABLE void qmlTest();

signals:
  void initProgressInfo(int value,QString msg);
  void itemRangeValid(QTreeWidgetItem *item,int status);
  void alarmError(quint16 devId,quint16 axisInx,bool hasError);//当checkStatus时，对外发送状态信息
  void netError(quint16 axisInx);

public slots:
  bool onReadPageFlash(int axis,QTreeWidget *pageTree);
  bool onWritePageFlash(int axis,QTreeWidget *pageTree);

private:
  bool checkPropertyParameters(QTreeWidgetItem *item);
  bool checkPowerBoardParameters(QTreeWidgetItem *item,const QMap<QString ,PowerBoardLimit> *limit);
  bool checkParameters(int axis,QTreeWidget *tree);
private:
  SevDevicePrivate *d_ptr;
};

#endif // SEVDEVICE_H
