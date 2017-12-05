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

class SevDevicePrivate
{
  Q_DECLARE_PUBLIC(SevDevice)
public :
  enum{
    SYSCONFIG_COL_NAME,
    SYSCONFIG_COL_PRM,
    SYSCONFIG_COL_CLASSNAME,
    SYSCONFIG_COL_XMLNAME,
    SYSCONFIG_COL_INDEX,
    SYSCONFIG_COL_ISGLOBAL
  }SysConfigColumnInx;

  SevDevicePrivate(SevDevice *sev);
  ~SevDevicePrivate();
  void init(const DeviceConfig *dConfig);
  QTreeWidget* configTree();
  QTreeWidgetItem* findTargetTree();
  //通信口
  //控制板
  //功率板
  //软件模块
  quint32 m_devId;
  quint8 m_comType;
  quint8 m_axisNum;
  QString m_typeName;//SD4x
  QString m_modeName;//SD42
  QString m_version;
  bool m_connected;

  quint32 m_pwrId;   //id->SD?? 通过一个id映射表获得名字
  quint32 m_ctrId;   //id->SD?? 通过一个id映射表获得名字
  quint32 m_fpgaId;

  ICtrBoard *m_ctrBoard;
  IPwrBoard *m_pwrBoard;
  IDspMap *m_dspMap;
  LinkSocket *m_socket;

  QString m_filePath;
  QTreeWidgetItem *m_targetTree;

protected:
  SevDevice *q_ptr;
private:
  QTreeWidget *m_configTree;


};

#endif // SEVDEVICEPRIVATE_P_H

