#ifndef SEVCTRBOARD_H
#define SEVCTRBOARD_H
#include <QObject>
#include "ictrboard.h"

class SevCtrBoard : public ICtrBoard
{
  Q_OBJECT
public:
  explicit SevCtrBoard(SevDevicePrivate *sev,QObject *parent = 0);
  ~SevCtrBoard();

signals:

public slots:
};

#endif // SEVCTRBOARD_H
