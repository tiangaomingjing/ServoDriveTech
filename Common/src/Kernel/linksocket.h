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

  bool readPageFlash(int axis,QTreeWidgetItem *item);
  bool writePageFlash(int axis,QTreeWidgetItem *item);


protected:


signals:

public slots:

private:
  SevDevicePrivate *q_ptr;
  bool m_isConnected;
  ComDriver::ICom *m_com;
  quint8 m_tryWriteCount;
};

#endif // LINKSOCKET_H
