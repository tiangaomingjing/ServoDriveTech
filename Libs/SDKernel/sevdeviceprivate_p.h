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
//  quint32 m_devId;
//  quint8 m_comType;
//  quint8 m_rnStationId;
//  quint8 m_axisNum;
//  QString m_typeName;//SD4x
//  QString m_modeName;//SD42
//  QString m_version;
  bool m_connected;

//  quint32 m_pwrId;   //id->SD?? 通过一个id映射表获得名字
//  quint32 m_ctrId;   //id->SD?? 通过一个id映射表获得名字
//  quint32 m_fpgaId;

  DeviceConfig *m_devConfig;
  ICtrBoard *m_ctrBoard;
  IPwrBoard *m_pwrBoard;
  IDspMap *m_dspMap;
  LinkSocket *m_socket;

  QString m_filePath;
  QTreeWidgetItem *m_targetTree;


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

