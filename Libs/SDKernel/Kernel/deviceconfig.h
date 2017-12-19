#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <QObject>


class DeviceConfig : public QObject
{
  Q_OBJECT
public:
  explicit DeviceConfig(QObject *parent = 0);
  ~DeviceConfig();
  quint32 m_devId;
  quint8 m_comType;
  quint8 m_axisNum;
  QString m_typeName;//SD4x
  QString m_modeName;//SD42
  QString m_version;

  quint32 m_pwrId;   //id->SD?? 通过一个id映射表获得名字
  quint32 m_ctrId;   //id->SD?? 通过一个id映射表获得名字
  quint32 m_fpgaId;

  quint8 m_rnStationId;
signals:

public slots:
};

#endif // DEVICECONFIG_H
