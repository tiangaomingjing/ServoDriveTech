#include "ictrboard.h"

ICtrBoard::ICtrBoard(SevDevicePrivate *sev, QObject *parent) : QObject(parent),q_ptr(sev)
{

}

