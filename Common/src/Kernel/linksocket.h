#ifndef LINKSOCKET_H
#define LINKSOCKET_H

#include <QObject>
#include "sdtglobaldef.h"

GT_USE_NAMESPACE
namespace ComDriver
{
  class ICom;
}

class SevDevice;
class LinkSocket : public QObject
{
  Q_OBJECT
public:
  static LinkSocket *instance(SevDevice *sev,ComDriver::ICom *com,QObject *parent = 0);
  ~LinkSocket();

  void connect(ComDriver::ICom *com);
  QString socketName()const;
  quint8 socketTypeId()const;
protected:
  explicit LinkSocket(SevDevice *sev,ComDriver::ICom *com,QObject *parent = 0);
  explicit LinkSocket(QObject *parent = 0);

signals:

public slots:

private:
  ComDriver::ICom *m_com;
  static LinkSocket *m_instance;
  static QMutex *m_mutex;
  SevDevice *q_ptr;
};

#endif // LINKSOCKET_H
