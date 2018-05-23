#ifndef SEVDEVICEPRIVATE_P_H
#define SEVDEVICEPRIVATE_P_H
#include <QObject>
class SevDevice;
class QTreeWidget;
class QTreeWidgetItem;
class ICtrBoard;
class IPwrBoard;
class IDspMap;
class LinkSocket;
class DeviceConfig;
class VerAttribute;
class GeneralCmd;

class SevDevicePrivate:public QObject
{
  Q_OBJECT
  Q_DECLARE_PUBLIC(SevDevice)
public :
  SevDevicePrivate(SevDevice *sev, QObject *parent=0);
  ~SevDevicePrivate();
  bool init(const DeviceConfig *dConfig);
  QTreeWidget* configTree();
  QTreeWidgetItem* findTargetTree();
  //通信口
  //控制板
  //功率板
  //软件模块
  //随版本属性附加类
  bool m_connected;

  LinkSocket *m_socket;
  ICtrBoard *m_ctrBoard;
  IPwrBoard *m_pwrBoard;
  IDspMap *m_dspMap;
  DeviceConfig *m_devConfig;
  VerAttribute *m_verAttribute;

  QString m_filePath;
  QTreeWidgetItem *m_targetTree;

  QString m_aliasName;
  int m_barCount;

signals:
  void initProgressInfo(int value,QString msg);

protected:
  SevDevice *q_ptr;
private:
  QTreeWidget *m_configTree;

private:
  void initConfig(const DeviceConfig *dConfig);
};

#endif // SEVDEVICEPRIVATE_P_H

