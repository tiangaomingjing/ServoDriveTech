#ifndef ICTRBOARD_H
#define ICTRBOARD_H

#include <QObject>

class SevDevice;
class ICtrBoard : public QObject
{
  Q_OBJECT
public:
  explicit ICtrBoard(SevDevice *sev,QObject *parent = 0);
  virtual~ICtrBoard(){}

signals:

public slots:

protected:
  SevDevice *q_ptr;
};

#endif // ICTRBOARD_H
