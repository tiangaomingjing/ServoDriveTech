#include "eprom_power.h"
#include "gtutils.h"

EPROM_POWER::EPROM_POWER(QString filePath, int16 com_type) : EPROM(filePath, com_type)
{
    m_baseAdd = getBaseAddress();
}

EPROM_POWER::~EPROM_POWER() {

}

int16 EPROM_POWER::writeEprom(int16 axis, Uint16 ofst, Uint8 *value, Uint16 num, int16 com_type, int16 stationId) {
    int16 result = GTSD_CMD_WriteEEPROMExt(axis, ofst, value, num, com_type, stationId);
    return result;
}

int16 EPROM_POWER::readEprom(int16 axis, Uint16 ofst, Uint8 *value, Uint16 num, int16 com_type, int16 stationId) {
    int16 result = GTSD_CMD_ReadEEPROMExt(axis, ofst, value, num, com_type, stationId);
    return result;
}

QTreeWidget* EPROM_POWER::createReadTree(Uint32 id) {
    QTreeWidget* powerIndex = TreeManager::createTreeWidgetFromXmlFile(GTUtils::databasePath() + "Board/PB/pbindex.ui");
    QString idStr = QString::number(id, 10);
    QTreeWidgetItem *powerIndexItem = GLO::findItem(idStr, powerIndex, TREE_VALUE);
    if (powerIndexItem == NULL) {
        return NULL;
    }
    QString powerPath = GLO::getPath(powerIndexItem);
    powerPath = GTUtils::databasePath() + "Board/PB/" + powerPath + "/" + idStr + "/" + idStr + ".ui";
    QTreeWidget* readTree = TreeManager::createTreeWidgetFromXmlFile(powerPath);
    return readTree;
}

int EPROM_POWER::getBaseAddress()
{
    QString boardPath = GTUtils::databasePath() + "Board/PB/";
    QString indexPath = boardPath + "pbindex.ui";
    QTreeWidget* indexTree = TreeManager::createTreeWidgetFromXmlFile(indexPath);
    QTreeWidgetItem *xmlBaseAdd;
    bool ok;
    xmlBaseAdd = GLO::findItem("xmlBaseAddress", indexTree, TREE_NAME);
    int baseAdd = xmlBaseAdd->text(TREE_VALUE).toInt(&ok, 10);
    delete indexTree;
    return baseAdd;
}
