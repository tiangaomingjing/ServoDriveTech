#include "ipwrboard.h"

IPwrBoard::IPwrBoard(SevDevice *sev, QObject *parent) : QObject(parent),q_ptr(sev)
{

}

