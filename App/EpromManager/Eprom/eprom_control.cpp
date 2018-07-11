#include "eprom_control.h"
#include "gtutils.h"

EPROM_CONTROL::EPROM_CONTROL(QString filePath, int16 com_type) : EPROM(filePath, com_type)
{
    m_baseAdd = getBaseAddress();
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
    QTreeWidget* controlIndex = TreeManager::createTreeWidgetFromXmlFile(GTUtils::databasePath() + "Board/CB/cbindex.ui");
    QString idStr = QString::number(id, 10);
    QTreeWidgetItem *controlIndexItem = GLO::findItem(idStr, controlIndex, TREE_NAME);
    if (controlIndexItem == NULL) {
        return NULL;
    }
    QString controlPath = GLO::getPath(controlIndexItem);
    controlPath = GTUtils::databasePath() + "Board/CB/" + controlPath + "/" + idStr + "/" + idStr + ".ui";
    QTreeWidget* readTree = TreeManager::createTreeWidgetFromXmlFile(controlPath);
    return readTree;
}

int EPROM_CONTROL::getBaseAddress()
{
    QString boardPath = GTUtils::databasePath() + "Board/CB/";
    QString indexPath = boardPath + "cbindex.ui";
    QTreeWidget* indexTree = TreeManager::createTreeWidgetFromXmlFile(indexPath);
    QTreeWidgetItem *xmlBaseAdd;
    bool ok;
    xmlBaseAdd = GLO::findItem("xmlBaseAddress", indexTree, TREE_NAME);
    int baseAdd = xmlBaseAdd->text(TREE_VALUE).toInt(&ok, 10);
    delete indexTree;
    return baseAdd;
}
