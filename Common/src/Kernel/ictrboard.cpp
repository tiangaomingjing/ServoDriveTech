#include "ictrboard.h"

ICtrBoard::ICtrBoard(SevDevice *sev,QObject *parent) : QObject(parent),q_ptr(sev)
{

}

