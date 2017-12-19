#include "ipwrboard.h"
#include <QDebug>

IPwrBoard::IPwrBoard(SevDevicePrivate *sev, QObject *parent) : QObject(parent),q_ptr(sev)
{

}

IPwrBoard::~IPwrBoard()
{
  qDebug()<<"IPwrBoard-->destruct";
}
