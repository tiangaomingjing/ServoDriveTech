#ifndef AUTOTURNNING_H
#define AUTOTURNNING_H

#include <QObject>
class SevDevice;

class AutoTurnning : public QObject
{
  Q_OBJECT
public:
  explicit AutoTurnning(QObject *parent = 0);


signals:

public slots:
private:
  quint16 readNos(quint16 axisInx);
};

#endif // AUTOTURNNING_H
