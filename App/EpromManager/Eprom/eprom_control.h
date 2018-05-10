#ifndef EPROM_CONTROL_H
#define EPROM_CONTROL_H

#include "eprom.h"

class EPROM_CONTROL : public EPROM
{
public:
    EPROM_CONTROL(QString filePath, int16 com_type);
    ~EPROM_CONTROL();
protected:
    int16 writeEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId);
    int16 readEprom(int16 axis, Uint16 ofst, Uint8* value, Uint16 num, int16 com_type, int16 stationId);
    QTreeWidget* createReadTree(Uint32 id);
    int getBaseAddress();
};

#endif // EPROM_CONTROL_H
