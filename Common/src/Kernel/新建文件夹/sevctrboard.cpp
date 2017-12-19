#include "sevctrboard.h"

#include <QDebug>

SevCtrBoard::SevCtrBoard(SevDevicePrivate *sev, QObject *parent) : ICtrBoard(sev,parent)
{

}
SevCtrBoard::~SevCtrBoard()
{
  qDebug()<<"SevCtrBoard-->destruct";
}

