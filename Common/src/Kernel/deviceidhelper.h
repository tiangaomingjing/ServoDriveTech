#ifndef DEVICEIDHELPER_H
#define DEVICEIDHELPER_H

#include <QObject>
namespace ComDriver {
  class ICom;
}

class DeviceIdHelper : public QObject
{
  Q_OBJECT
public:
  typedef enum
  {
    COL_IDMAP_ID,
    COL_IDMAP_TYPE,
    COL_IDMAP_MODE,
    COL_IDMAP_NICKNAME,
    COL_IDMAP_AXISNUM
  }IdMapColumn;
  explicit DeviceIdHelper(ComDriver::ICom *com,QObject *parent = 0);
  ~DeviceIdHelper();

  quint32 readPwrId();
  quint32 readCtrId();
  quint32 readFpgaId();
  QString readVersion();
  QString modeNameFromIdMap();
  QString typeNameFromIdMap();
  quint8 axisNumFromIdMap();

signals:

public slots:
private:
  ComDriver::ICom *m_com;
  quint32 m_pwrId;
  quint32 m_ctrId;
  quint32 m_fpgaId;
  QString m_typeName;
  QString m_modeName;
  quint8 m_axisNum;
};

#endif // DEVICEIDHELPER_H
