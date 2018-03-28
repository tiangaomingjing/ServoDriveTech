#ifndef LINKSOCKET_H
#define LINKSOCKET_H

#include <QObject>
#include "sdtglobaldef.h"

GT_USE_NAMESPACE
namespace ComDriver
{
  class ICom;
}

class SevDevicePrivate;
class QTreeWidgetItem;
class GeneralCmd;

class LinkSocket : public QObject
{
  Q_OBJECT
public:
   explicit LinkSocket(SevDevicePrivate *sev,QObject *parent = 0);
  ~LinkSocket();

  bool connect(void (*processCallBack)(void *argv, short *value), void *uiProcessBar);
  void disConnect();
  QString socketName()const;
  quint8 socketTypeId()const;
  bool isConnected() const;
  void setTryWriteCount(quint8 tryWriteCount);

  bool readItemFlash(int axis,QTreeWidgetItem *item);
  bool writeItemFlash(int axis,QTreeWidgetItem *item);


  //通用RAM读写操作
  quint64 genCmdRead(const QString &cmdReadName,qint16 axisIndex,bool &isOk);
  bool genCmdWrite(const QString &cmdWriteName,quint64 value,qint16 axisIndex);
  qint16 genReadErrorCode();
  bool containsCmd(const QString &cmdName);

  ComDriver::ICom *comObject() const;

  bool adjust(void (*processCallBack)(void *argv, short *value), void *uiProcessBar);

  bool clearAlarm(quint16 axisInx);

protected:


signals:

public slots:

private:
  SevDevicePrivate *q_ptr;
  bool m_isConnected;
  ComDriver::ICom *m_com;
  quint8 m_tryWriteCount;
  GeneralCmd *m_genCmd;
};

#endif // LINKSOCKET_H
