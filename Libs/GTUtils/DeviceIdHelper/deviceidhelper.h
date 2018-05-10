#ifndef DEVICEIDHELPER_H
#define DEVICEIDHELPER_H

#include <QObject>
#include "gtutils_global.h"

class QTreeWidget;

namespace ComDriver {
  class ICom;
}

class GTUTILSSHARED_EXPORT DeviceIdHelper : public QObject
{
  Q_OBJECT
public:
  explicit DeviceIdHelper(QObject *parent = 0);
  explicit DeviceIdHelper(ComDriver::ICom *com,QObject *parent = 0);
  ~DeviceIdHelper();

  void setCom(ComDriver::ICom *com);
  quint32 readPwrId(bool &isOk);
  quint32 readCtrId(bool &isOk);
  quint32 readFpgaId(bool &isOk);
  bool readFpgaDate(quint16 &year, quint16 &day);
  QString readVersion(bool &isOk);

  QString modeNameFromIdMap(quint32 pwrId);
  QString typeNameFromIdMap(quint32 pwrId);
  quint8 axisNumFromIdMap(quint32 pwrId);

  bool databaseHasPwrId() const;

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
  bool m_hasPwrId;
};

#endif // DEVICEIDHELPER_H
