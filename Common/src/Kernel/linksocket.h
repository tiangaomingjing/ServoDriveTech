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
  explicit LinkSocket(SevDevice *sev,ComDriver::ICom *com,QObject *parent = 0);
  ~LinkSocket();

  void connect(ComDriver::ICom *com);

signals:

public slots:

private:
  ComDriver::ICom *m_com;
  SevDevice *q_ptr;
};

#endif // LINKSOCKET_H
