#ifndef ICTRBOARD_H
#define ICTRBOARD_H

#include <QObject>

class SevDevicePrivate;
class ICtrBoard : public QObject
{
  Q_OBJECT
public:
  explicit ICtrBoard(SevDevicePrivate *sev,QObject *parent = 0);
  virtual~ICtrBoard(){}

signals:

public slots:

protected:
  SevDevicePrivate *q_ptr;
};

#endif // ICTRBOARD_H
