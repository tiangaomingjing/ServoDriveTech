#ifndef APPMAINWINDOWTEST_H
#define APPMAINWINDOWTEST_H

#include <QMainWindow>
#include "icom.h"
#include <QList>

class QTreeWidget;
class QTreeWidgetItem;

namespace Ui {
class AppMainWindowTest;
}
namespace ComDriver {
class ICom;
}

namespace GT
{
class SevDevice;
class IDevice
{
public:
  IDevice(){}
  virtual ~IDevice(){}
  virtual bool init()=0;
};
class DeviceConfig
{
public:
  DeviceConfig(){}
  ~DeviceConfig(){}

  quint32 m_devId;
  quint8 m_comType;
  quint8 m_axisNum;
  QString m_typeName;//SD4x
  QString m_modeName;//SD42
  quint32 m_version;

  quint32 m_pwrId;   //id->SD?? 通过一个id映射表获得名字
  quint32 m_ctrId;   //id->SD?? 通过一个id映射表获得名字
};

class IDevReadWriter:public QObject
{
  Q_OBJECT
public:
  explicit IDevReadWriter(QTreeWidget *idMapTree,QObject *parent=0):QObject(parent),m_idMapTree(idMapTree){}
  virtual ~IDevReadWriter(){}
  virtual DeviceConfig readConfig(ComDriver::ICom *icom,bool &isOk)=0;
  virtual bool writeConfig(const DeviceConfig &config)=0;
protected:
  QTreeWidget *m_idMapTree;
};

class GlobalConfig
{
public:
  GlobalConfig();
  ~GlobalConfig();
};

class LinkSocket
{
public:
  LinkSocket(SevDevice *sev,ComDriver::ICom *com):m_com(com),q_ptr(sev){}
  ~LinkSocket(){}

  void connect(ComDriver::ICom *com)
  {
    m_com=com;
  }

private:
  ComDriver::ICom *m_com;
  SevDevice *q_ptr;
};

class ICtrBoard
{
public:
  ICtrBoard(SevDevice *sev):q_ptr(sev){}
  virtual~ICtrBoard(){}
protected:
  SevDevice *q_ptr;
};
class IPwrBoard
{
public:
  IPwrBoard(SevDevice *sev):q_ptr(sev){}
  virtual ~IPwrBoard(){}
protected:
  SevDevice *q_ptr;
};
class AxisTreeMap:public QObject
{
public:
  AxisTreeMap(QObject *parent=0):QObject(parent){}
  ~AxisTreeMap(){}
  QList<QTreeWidget *>m_axisTreeList;
  QList<QTreeWidget *>m_globalTreeList;
};

class IDspMap:public QObject
{
public:
  explicit IDspMap(SevDevice *sev,QObject *parent=0):QObject(parent),q_ptr(sev){}
  virtual ~IDspMap(){}
  virtual bool initTreeMap()=0;
protected:
  SevDevice *q_ptr;
  QList<AxisTreeMap*>m_treeMapList;
  QTreeWidget *m_ramTree;
  QTreeWidget *m_flashTree;
};

class SevDevice:public QObject
{
  Q_OBJECT
public:
  explicit SevDevice(ComDriver::ICom *com,const DeviceConfig *dConfig,QObject *parent=0):QObject(parent),\
    m_socket(new LinkSocket(this,com)),m_config(dConfig)
  {

  }
  ~SevDevice(){}
  void adjustSocket(ComDriver::ICom *com)
  {
    m_socket->connect(com);
  }
  //通信口
  //控制板
  //功率板
  //软件模块
  const DeviceConfig *m_config;
  ICtrBoard *m_ctrBoard;
  IPwrBoard *m_pwrBoard;
  IDspMap *m_dspMap;
  LinkSocket *m_socket;
};

class IUiControler:public QObject
{
public:
  explicit IUiControler(SevDevice *sev,GlobalConfig *gconfig,QObject *parent=0):QObject(parent)\
  ,m_sev(sev),m_gConfig(gconfig){}
  virtual ~IUiControler(){}
  SevDevice *m_sev;
  GlobalConfig *m_gConfig;
};
class SevUiControler:public IUiControler
{
public:
  explicit SevUiControler(SevDevice *sev,GlobalConfig *gconfig,QObject *parent=0):IUiControler(sev,gconfig,parent){}
  ~SevUiControler(){}
};

class SdAssembly:public QObject
{
public:
  explicit SdAssembly(QObject *parent=0):QObject(parent){}
  ~SdAssembly();
  SevDevice *m_device;
  IUiControler *m_uiControler;
  GlobalConfig *m_gConfig;
};

}
class AppMainWindowTest : public QMainWindow
{
  Q_OBJECT

public:
  explicit AppMainWindowTest(QWidget *parent = 0);
  ~AppMainWindowTest();

private:
  void initial();

private:
  Ui::AppMainWindowTest *ui;
};

#endif // APPMAINWINDOWTEST_H
