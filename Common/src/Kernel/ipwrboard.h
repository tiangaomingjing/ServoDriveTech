#ifndef IPWRBOARD_H
#define IPWRBOARD_H

#include <QObject>
class SevDevice;
class IPwrBoard : public QObject
{
  Q_OBJECT
public:
  explicit IPwrBoard(SevDevice *sev,QObject *parent = 0);
  virtual ~IPwrBoard(){}

signals:

public slots:

protected:
  SevDevice *q_ptr;
};

#endif // IPWRBOARD_H
