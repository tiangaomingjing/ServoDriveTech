#ifndef SEVDEVICE_H
#define SEVDEVICE_H

#include <QObject>

namespace ComDriver {
class ICom;
}
namespace GT {
class DeviceConfig;
}

class LinkSocket;
class ICtrBoard;
class IPwrBoard;
class IDspMap;

class SevDevice : public QObject
{
  Q_OBJECT
public:
  explicit SevDevice(ComDriver::ICom *com,const GT::DeviceConfig *dConfig,QObject *parent=0);
  ~SevDevice(){}
  void adjustSocket(ComDriver::ICom *com);
  //通信口
  //控制板
  //功率板
  //软件模块
  const GT::DeviceConfig *m_config;
  ICtrBoard *m_ctrBoard;
  IPwrBoard *m_pwrBoard;
  IDspMap *m_dspMap;
  LinkSocket *m_socket;

signals:

public slots:
};

#endif // SEVDEVICE_H
