#include "idspmap.h"

IDspMap::IDspMap(SevDevicePrivate *sev, QObject *parent):QObject(parent),q_ptr(sev),m_ramTree(NULL),m_flashTree(NULL)
{

}

IDspMap::~IDspMap()
{

}
