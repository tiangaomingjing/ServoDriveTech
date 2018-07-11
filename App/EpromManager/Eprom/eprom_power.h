#ifndef EPROM_POWER_H
#define EPROM_POWER_H

#include "eprom.h"

class EPROM_POWER : public EPROM
{
public:
    EPROM_POWER(QString filePath, int16 com_type);
    ~EPROM_POWER();
protected:
    int16 writeEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId);
    int16 readEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId);
    QTreeWidget* createReadTree(Uint32 id);
    int getBaseAddress();
};

#endif // EPROM_POWER_H
