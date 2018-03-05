#ifndef DEVICEIDHELPER_H
#define DEVICEIDHELPER_H

#include <QObject>
#include "gtutils_global.h"

namespace ComDriver {
  class ICom;
}

class GTUTILSSHARED_EXPORT DeviceIdHelper : public QObject
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
  explicit DeviceIdHelper(QObject *parent = 0);
  explicit DeviceIdHelper(ComDriver::ICom *com,QObject *parent = 0);
  ~DeviceIdHelper();

  void setCom(ComDriver::ICom *com);
  quint32 readPwrId(bool &isOk);
  quint32 readCtrId(bool &isOk);
  quint32 readFpgaId(bool &isOk);
  QString readVersion(bool &isOk);
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
