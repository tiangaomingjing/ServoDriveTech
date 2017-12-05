#ifndef IPWRBOARD_H
#define IPWRBOARD_H

#include <QObject>
class SevDevicePrivate;
class IPwrBoard : public QObject
{
  Q_OBJECT
public:
  explicit IPwrBoard(SevDevicePrivate *sev,QObject *parent = 0);
  virtual ~IPwrBoard(){}

signals:

public slots:

protected:
  SevDevicePrivate *q_ptr;
};

#endif // IPWRBOARD_H
