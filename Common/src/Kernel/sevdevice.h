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

class SevDevice : public QObject
{
  Q_OBJECT
public:
  explicit SevDevice(const DeviceConfig *dConfig,QObject *parent=0);
  ~SevDevice(){}
  void adjustSocket(ComDriver::ICom *com);
  //通信口
  //控制板
  //功率板
  //软件模块
  quint32 m_devId;
  quint8 m_comType;
  quint8 m_axisNum;
  QString m_typeName;//SD4x
  QString m_modeName;//SD42
  quint32 m_version;

  quint32 m_pwrId;   //id->SD?? 通过一个id映射表获得名字
  quint32 m_ctrId;   //id->SD?? 通过一个id映射表获得名字

  ICtrBoard *m_ctrBoard;
  IPwrBoard *m_pwrBoard;
  IDspMap *m_dspMap;
  LinkSocket *m_socket;

signals:

public slots:
};

#endif // SEVDEVICE_H
