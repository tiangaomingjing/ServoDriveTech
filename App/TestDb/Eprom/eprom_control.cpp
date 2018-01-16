#include "eprom_control.h"

EPROM_CONTROL::EPROM_CONTROL(QString filePath, int16 com_type) : EPROM(filePath, com_type)
{

}

EPROM_CONTROL::~EPROM_CONTROL() {

}

int16 EPROM_CONTROL::writeEprom(int16 axis, Uint16 ofst, Uint8 *value, Uint16 num, int16 com_type, int16 stationId) {
    int16 result = GTSD_CMD_WriteEEPROM(axis, ofst, value, num, com_type, stationId);
    return result;
}

int16 EPROM_CONTROL::readEprom(int16 axis, Uint16 ofst, Uint8 *value, Uint16 num, int16 com_type, int16 stationId) {
    int16 result = GTSD_CMD_ReadEEPROM(axis, ofst, value, num, com_type, stationId);
    return result;
}

QTreeWidget* EPROM_CONTROL::createReadTree(Uint32 id) {
    QTreeWidget* controlIndex = TreeManager::createTreeWidgetFromXmlFile(RESOURCE_FILE_PATH + "CB/cbindex.ui");
    QString idStr = QString::number(id, 10);
    QTreeWidgetItem *controlIndexItem = GLO::findItem(idStr, controlIndex, TREE_VALUE);
    if (controlIndexItem == NULL) {
        return NULL;
    }
    QString controlPath = GLO::getPath(controlIndexItem);
    controlPath = RESOURCE_FILE_PATH + "CB/" + controlPath;
    QTreeWidget* readTree = TreeManager::createTreeWidgetFromXmlFile(controlPath);
    return readTree;
}
