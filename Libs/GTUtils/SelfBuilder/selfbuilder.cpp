#include "gtutils.h"
#include "qttreemanager.h"
#include "selfbuilder.h"

#include <QFile>
#include <QTextStream>
#include <QTreeWidget>
#include <QDebug>
#include <QDir>
#include <QByteArray>
#include <QMessageBox>

#define POWER_BASEADDR 64

using namespace ComDriver;

SelfBuilder::SelfBuilder(ComDriver::ICom *com)
{
    m_com = com;
    //m_type = m_com->iComType();;
    m_type = ICOM_TYPE_RNNET;
}

SELFBUILDER_RTN SelfBuilder::buildFromEprom(void (*processCallback)(void *pbar,short *value),void *processbar, BuilderParameters *parameters)
{
    m_powerID = QString::number(parameters->m_pwrId);
    m_controlID = QString::number(parameters->m_ctrId);
    m_version = parameters->m_version;
    SELFBUILDER_RTN rtn;
    rtn = initParameters();
    if (rtn != SELFBUILDER_SUCCESS) {
        return rtn;
    }
    rtn = buildPower(processCallback, processbar);
    if (rtn != SELFBUILDER_SUCCESS) {
        return rtn;
    }
    rtn = buildControl();
    if (rtn != SELFBUILDER_SUCCESS) {
        return rtn;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::buildPower(void (*processCallback)(void *pbar,short *value),void *processbar)
{
    QString boardPath = GTUtils::databasePath() + "Board/PB/";
    QString indexPath = boardPath + "pbindex.ui";
    QString pwrMapPath = boardPath + "IdMap_Power.ui";
    QString selectPath = GTUtils::sysPath() + "SysMap/ConfigSelectTree.ui";
    QString databaseSelPath = GTUtils::databasePath() + "Board/SelectTree.ui";
    SELFBUILDER_RTN rtn;
    if (!axisNumExisted(QString::number(m_axisNum), pwrMapPath)) {
        qDebug()<<"no such product";
        QMessageBox::warning(0, QObject::tr("Warning"), QObject::tr("No such product. Please update the software."));
        return SELFBUILDER_NOPRODUCT;
    }
    if (!idExisted(m_powerID, pwrMapPath)) {
        //pwrID nonexist
        rtn = addModeToIdMap(m_powerID, pwrMapPath);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addNewDatabase(m_powerID, boardPath, indexPath);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addIndexTree(indexPath, m_powerID);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addSelectTree(selectPath, m_powerID);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addDatabaseSelectTree(databaseSelPath);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addSysConfig(processCallback, processbar);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addSystemMap();
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
    } else if (!versionExisted(m_version, selectPath)) {
        //pwrID exist while version nonexist
        rtn = addDatabaseVersion(m_powerID, boardPath);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addSelectTree(selectPath, m_powerID);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addSysConfig(processCallback, processbar);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addSystemMap();
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::buildControl()
{
    QString boardPath = GTUtils::databasePath() + "Board/CB/";
    QString indexPath = boardPath + "cbindex.ui";
    QString ctrMapPath = boardPath + "IdMap_Control.ui";
    SELFBUILDER_RTN rtn;
    if (!axisNumExisted(QString::number(m_axisNum), ctrMapPath)) {
        qDebug()<<"no such product";
        QMessageBox::warning(0, QObject::tr("Warning"), QObject::tr("No such product. Please update the software."));
        return SELFBUILDER_NOPRODUCT;
    }
    if (!idExisted(m_controlID, ctrMapPath)) {
        //pwrID nonexist
        rtn = addModeToIdMap(m_controlID, ctrMapPath);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addNewCtrDatabase(m_controlID, boardPath, indexPath);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
        rtn = addIndexTree(indexPath, m_controlID);
        if (rtn != SELFBUILDER_SUCCESS) {
            return rtn;
        }
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::initParameters()
{
    // read axisNum, product type, series num from hardware
    uint16_t ofst = 1 + POWER_BASEADDR;
    uint8_t value[4];
    uint16_t num = 2;
    uint8_t cs = 0;
    errcode_t ret;
    ret = m_com->readEEPROM(ofst, value, num, cs);
    if (ret != 0) {
        return SELFBUILDER_READPRODUCTERR;
    }
    QByteArray tempByte;
    tempByte.append(value[0]);
    if (value[1] != 0) {
        tempByte.append(value[1]);
    }
    m_product = QString::fromLatin1(tempByte);

    ofst = 3 + POWER_BASEADDR;
    ret = m_com->readEEPROM(ofst, value, num, cs);
    if (ret != 0) {
        return SELFBUILDER_READAXISERR;
    }
    double tempValue = 0;
    for (int j = 0; j < num; j++) {
        tempValue = tempValue + (value[j] << (j * 8));
    }
    m_axisNum = tempValue;

    ofst = 5 + POWER_BASEADDR;
    ret = m_com->readEEPROM(ofst, value, num, cs);
    if (ret != 0) {
        return SELFBUILDER_READSERIESERR;
    }
    tempValue = 0;
    for (int j = 0; j < num; j++) {
        tempValue = tempValue + (value[j] << (j * 8));
    }
    m_series = QString::number(tempValue);

//    m_product = "M";
//    m_axisNum = 6;
//    m_series = "1";

    m_modeCreated = false;
    return SELFBUILDER_SUCCESS;
}

bool SelfBuilder::idExisted(const QString &id, const QString &path)
{
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        return false;
    }
    QTreeWidgetItem* item = GTUtils::findItem(id, tree, IDMAP_ID);
    if (item == NULL) {
        delete tree;
        return false;
    }
    m_typeName = item->text(IDMAP_TYPE);
    m_modeName = item->text(IDMAP_MODE);
    delete tree;
    return true;
}

bool SelfBuilder::versionExisted(const QString &ver, const QString &path)
{
    // return true while version exists
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        qDebug()<<"no path";
        return false;
    }
    QString type;
    if (m_type == ICOM_TYPE_PCDEBUG) {
        type = "PcDebug";
    } else if (m_type == ICOM_TYPE_RNNET) {
        type = "RnNet";
    }
    QTreeWidgetItem *comItem = GTUtils::findItem(type, tree, CONFIG_NAME);
    if (comItem == NULL) {
        qDebug()<<"com type non-exist";
        return false;
    }
    QTreeWidgetItem *typeItem = GTUtils::findItemInItem(m_typeName, comItem, CONFIG_NAME);
    if (typeItem == NULL) {
        qDebug()<<"type name non-exist";
        return false;
    }
    QTreeWidgetItem *modeItem = GTUtils::findItemInItem(m_modeName, typeItem, CONFIG_NAME);
    if (modeItem == NULL) {
        qDebug()<<"mode name non-exist";
        return false;
    }
    QTreeWidgetItem *versionItem = GTUtils::findItemInItem(ver, modeItem, CONFIG_NAME);
    delete tree;
    if (versionItem == NULL) {
        return false;
    }
    return true;
}

bool SelfBuilder::ctrVerExisted(const QString &ver, const QString &path)
{
    QDir dir(path);
    if (!dir.exists()) {
        return "";
    }
    dir.setFilter(QDir::Dirs);
    QFileInfoList list = dir.entryInfoList();
    QString tempVer;
    for (int i = 0; i < list.count(); i++) {
        QFileInfo fileInfo = list.at(i);
        QString dirName = fileInfo.baseName();
        tempVer = dirName.right(dirName.length() - 1);
        if (tempVer.compare(ver) == 0) {
            return true;
        }
    }
    return false;
}

SELFBUILDER_RTN SelfBuilder::addModeToIdMap(const QString &id, const QString &path)
{
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        return SELFBUILDER_CREATETREEERR;
    }
    bool ok;
    if (!m_modeCreated) {
        m_typeName = "SD" + QString::number(m_axisNum) +"x";
        QString filePath = GTUtils::sysPath() + m_typeName + "/Index.ini";
        ok = createNewModeName(filePath);
        if (!ok) {
            delete tree;
            return SELFBUILDER_NEWMODEERR;
        }
        m_modeCreated = true;
    }
    QStringList list;
    list<<id<<m_typeName<<m_modeName<<"nick"<<QString::number(m_axisNum);
    tree->addTopLevelItem(new QTreeWidgetItem(list));
    ok = QtTreeManager::writeTreeWidgetToXmlFile(path, tree);
    delete tree;
    if (!ok) {
        return SELFBUILDER_WRITETREEERR;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addNewDatabase(const QString &id, const QString &path, const QString &indexPath) {
    QString idPath = path + m_product + "/" + m_product + QString::number(m_axisNum) +
                     "/series" + m_series + "/" + id +"/";
    QString versionPath = idPath + "filter/" + m_version + "/";
    QString oldIdPath = path + getOldPath(indexPath);
    m_newestVersion = getNewestVersion(oldIdPath + "filter/");
    QString oldVersionPath = oldIdPath + "filter/" + m_newestVersion + "/";

    bool ok = createSysPath(versionPath);
    if (!ok) {
        return SELFBUILDER_CREATEPATHERR;
    }
    ok = copyFileToPath(oldIdPath + m_newestID + ".ui", idPath + id + ".ui", false);
    if (!ok) {
        return SELFBUILDER_COPYERR;
    }
    ok = copyFileToPath(oldVersionPath + m_newestVersion + ".ui", versionPath + m_version + ".ui", false);
    if (!ok) {
        return SELFBUILDER_COPYERR;
    }
    SELFBUILDER_RTN rtn = readDataFromEEprom(idPath + id + ".ui", true);
    if (rtn != SELFBUILDER_SUCCESS) {
        return rtn;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addNewCtrDatabase(const QString &id, const QString &path, const QString &indexPath)
{
    QString idPath = path + m_product + "/" + m_product + QString::number(m_axisNum) +
                     "/series" + m_series + "/" + id +"/";
    QString oldIdPath = path + getOldPath(indexPath);
    bool ok = createSysPath(idPath);
    if (!ok) {
        return SELFBUILDER_CREATEPATHERR;
    }
    ok = copyFileToPath(oldIdPath + m_newestID + ".ui", idPath + id + ".ui", false);
    if (!ok) {
        return SELFBUILDER_COPYERR;
    }
    SELFBUILDER_RTN rtn = readDataFromEEprom(idPath + id + ".ui", false);
    if (rtn != SELFBUILDER_SUCCESS) {
        return rtn;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addIndexTree(const QString &path, const QString &id)
{
    QTreeWidget* indexTree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (indexTree == NULL) {
        return SELFBUILDER_CREATETREEERR;
    }
    QTreeWidgetItem* basicItem = indexTree->topLevelItem(1);
    QStringList list;
    list<<m_product<<m_product;
    QTreeWidgetItem* item = addBasicChild(basicItem, list);
    list.clear();
    list<<m_product + QString::number(m_axisNum)<<QString::number(m_axisNum);
    QTreeWidgetItem* item_1 = addBasicChild(item, list);
    list.clear();
    list<<"series" + m_series<<m_series;
    QTreeWidgetItem* item_2 = addBasicChild(item_1, list);
    list.clear();
    list<<"Nick"<<id;
    addBasicChild(item_2, list);
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, indexTree);
    delete indexTree;
    if (!ok) {
        return SELFBUILDER_WRITETREEERR;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addSelectTree(const QString &path, const QString &id)
{
    QTreeWidget *selectTree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (selectTree == NULL) {
        return SELFBUILDER_CREATETREEERR;
    }
    QTreeWidgetItem* basicItem;
    if (m_type == ICOM_TYPE_PCDEBUG) {
        basicItem = selectTree->topLevelItem(0);
    } else if (m_type == ICOM_TYPE_RNNET) {
        basicItem = selectTree->topLevelItem(1);
    }
    QStringList list;
    list<<m_typeName<<QString::number(m_axisNum)<<""<<"";
    QTreeWidgetItem* item = addBasicChild(basicItem, list);
    list.clear();
    list<<m_modeName<<QString::number(m_axisNum)<<id<<"";
    QTreeWidgetItem* item_1 = addBasicChild(item, list);
    list.clear();
    list<<m_version<<"NULL"<<"0"<<"";
    addBasicChild(item_1, list);
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, selectTree);
    delete selectTree;
    if (!ok) {
        return SELFBUILDER_WRITETREEERR;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addDatabaseSelectTree(const QString &path)
{
    QTreeWidget *selectTree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (selectTree == NULL) {
        return SELFBUILDER_CREATETREEERR;
    }
    QTreeWidgetItem* basicItem = selectTree->invisibleRootItem();
    QStringList list;
    list<<m_typeName<<"";
    QTreeWidgetItem* item = addBasicChild(basicItem, list);
    list.clear();
    list<<m_modeName<<QString::number(m_axisNum / 2);
    addBasicChild(item, list);
    list.clear();
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, selectTree);
    delete selectTree;
    if (!ok) {
        return SELFBUILDER_WRITETREEERR;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addSysConfig(void (*processCallback)(void *pbar,short *value),void *processbar)
{
    QString toDir = GTUtils::sysPath() + m_typeName + "/" + m_modeName + "/" + m_version + "/";
    QString fromDir = GTUtils::sysPath() + m_newestType + "/" + m_newestMode + "/" + m_newestVersion + "/";
    bool ok = copyDirectoryFiles(fromDir, toDir, true);
    if (!ok) {
        return SELFBUILDER_COPYERR;
    }
    //use huanglian's interface to deal with the xml documents
    SELFBUILDER_RTN rtn = changeDocuments(processCallback, processbar, toDir);
    if (rtn != SELFBUILDER_SUCCESS) {
        return rtn;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addSystemMap()
{
    QString comType;
    if (m_type == ICOM_TYPE_PCDEBUG) {
        comType = "PcDebug";
    } else if (m_type == ICOM_TYPE_RNNET) {
        comType = "RnNet";
    }
    QString tempDir = GTUtils::sysPath() + "SysMap/" + comType + "/" + m_typeName + "/" + m_modeName + "/" + m_version + "/";
    QString toDir = tempDir + "TargetTree.ui";
    QString fromDir = GTUtils::sysPath() + "SysMap/" + comType + "/" + m_newestType + "/" + m_newestMode + "/" + m_newestVersion + "/TargetTree.ui";
    bool ok = createSysPath(tempDir);
    if (!ok) {
        return SELFBUILDER_CREATEPATHERR;
    }
    ok = copyFileToPath(fromDir, toDir, true);
    if (!ok) {
        return SELFBUILDER_COPYERR;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::addDatabaseVersion(const QString &id, const QString &path)
{
    QString idPath = path + m_product + "/" + m_product + QString::number(m_axisNum) +
                     "/series" + m_series + "/" + id +"/";
    QString versionPath = idPath + "filter/" + m_version + "/";
    m_newestVersion = getNewestVersion(idPath + "filter/");
    QString oldVersionPath = idPath + "filter/" + m_newestVersion + "/";
    bool ok = createSysPath(versionPath);
    if (!ok) {
        return SELFBUILDER_CREATEPATHERR;
    }
    ok = copyFileToPath(oldVersionPath + m_newestVersion + ".ui", versionPath + m_version + ".ui", false);
    if (!ok) {
        return SELFBUILDER_COPYERR;
    }
    return SELFBUILDER_SUCCESS;
}

QTreeWidgetItem* SelfBuilder::addBasicChild(QTreeWidgetItem *item, const QStringList &list)
{
    for (int i = 0; i < item->childCount(); i++) {
        if (item->child(i)->text(INDEX_NAME).compare(list.at(0)) == 0) {
            return item->child(i);
        }
    }
    item->addChild(new QTreeWidgetItem(list));
    return item->child(item->childCount() - 1);
}

QString SelfBuilder::getOldPath(const QString &indexPath)
{
    QTreeWidget* indexTree = QtTreeManager::createTreeWidgetFromXmlFile(indexPath);
    QTreeWidgetItem *newestItem = GTUtils::findItem(m_newestID, indexTree, INDEX_NAME);
    QString result = m_newestID + "/";
    int count = 0;
    QTreeWidgetItem *currentItem = newestItem;
    while (count < 3) {
        currentItem = currentItem->parent();
        result = currentItem->text(INDEX_NAME) + "/" + result;
        count++;
    }
    delete indexTree;
    return result;
}

SELFBUILDER_RTN SelfBuilder::readDataFromEEprom(const QString &path, bool isPwr)
{
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        return SELFBUILDER_CREATETREEERR;
    }
    SELFBUILDER_RTN rtn = readTreeData(tree->invisibleRootItem(), isPwr);
    if (rtn != SELFBUILDER_SUCCESS) {
        return rtn;
    }
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, tree);
    delete tree;
    if (!ok) {
        return SELFBUILDER_WRITETREEERR;
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::readTreeData(QTreeWidgetItem *item, bool isPwr)
{
    for (int i = 0; i < item->childCount(); i++) {
        if (item->child(i)->text(TREE_ADDRESS).compare("0x0001") == 0) {
            item->child(i)->setText(TREE_VALUE, m_product);
        } else if (item->child(i)->text(TREE_ADDRESS).compare("0x0000") == 0) {

        } else if (item->child(i)->text(TREE_ADDRESS).compare("0x0003") == 0) {
            item->child(i)->setText(TREE_VALUE, QString::number(m_axisNum));
        } else if (item->child(i)->text(TREE_ADDRESS).compare("0x0005") == 0) {
            item->child(i)->setText(TREE_VALUE, m_series);
        } else if (item->child(i)->text(TREE_ADDRESS).compare("-1") != 0 && item->child(i)->text(TREE_ADDRESS).compare("") != 0) {
            bool ok;
            uint16_t ofst = item->child(i)->text(TREE_ADDRESS).toUShort(&ok, 16);
            uint8_t value[4];
            QString numType = item->child(i)->text(TREE_TYPE);
            uint16_t num;
            if (numType.compare("Uint8") == 0 || numType.compare("int8") == 0) {
                num = 1;
            } else if (numType.compare("Uint16") == 0 || numType.compare("int16") == 0) {
                num = 2;
            } else if (numType.compare("Uint32") == 0 || numType.compare("int32") == 0) {
                num = 4;
            }
            uint8_t cs = 0;
            if (isPwr) {
                cs = 0;
            } else {
                cs = 1;
            }
            errcode_t ret = m_com->readEEPROM(ofst, value, num, cs);
            if (ret != 0) {
                return SELFBUILDER_READTREEERR;
            }
            double tempValue = 0;
            double scale = item->child(i)->text(TREE_SCALE).toDouble();
            for (int j = 0; j < num; j++) {
                tempValue = tempValue + (value[j] << (j * 8));
            }
            if (numType.compare("int8") == 0) {
                int8_t tempValueTwo = tempValue;
                item->child(i)->setText(TREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
            } else if (numType.compare("int16") == 0) {
                int16_t tempValueTwo = tempValue;
                item->child(i)->setText(TREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
            } else if (numType.compare("int32") == 0) {
                int32_t tempValueTwo = tempValue;
                item->child(i)->setText(TREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
            } else {
                item->child(i)->setText(TREE_VALUE, QString::number(tempValue / scale, 'g', 8));
            }
        }
        readTreeData(item->child(i), isPwr);
    }
    return SELFBUILDER_SUCCESS;
}

SELFBUILDER_RTN SelfBuilder::changeDocuments(void (*processCallback)(void *, short *), void *processbar, const QString &path)
{
    QString path_allAxis = path + "FlashPrm_AllAxis.xml";
    QString path_axis0 = path + "page/PrmRAMAxis0.xml";
    QString path_axis1 = path + "page/PrmRAMAxis1.xml";
    char* pFileNameList[3];
    int pFileTypeList[3];
    pFileTypeList[0] = 0;
    pFileTypeList[1] = 0;
    pFileTypeList[2] = 0;
    int num = 3;
    uint8_t axis = 0;
    int size = path_allAxis.length();
    char *p = (char *)malloc(size + 1);
    memset(p, 0, size + 1);
    memcpy_s(p, size, path_allAxis.toStdString().c_str(), size);
    pFileNameList[0] = p;
    size = path_axis0.length();
    p = (char *)malloc(size + 1);
    memset(p, 0, size + 1);
    memcpy_s(p, size, path_axis0.toStdString().c_str(), size);
    pFileNameList[1] = p;
    size = path_axis1.size();
    p = (char *)malloc(size + 1);
    memset(p, 0, size + 1);
    memcpy_s(p, size, path_axis1.toStdString().c_str(),size);
    pFileNameList[2] = p;

    short count = 0;
    qDebug()<<"1"<<pFileNameList[0];
    qDebug()<<"2"<<pFileNameList[1];
    qDebug()<<"3"<<pFileNameList[2];
    errcode_t ret = m_com->readXML(axis, pFileNameList, pFileTypeList, num, processCallback, processbar, count);
    qDebug()<<"ret"<<ret;
    for (int i = 0; i < num; i++)
    {
        free(pFileNameList[i]);
    }
    if (ret != 0) {
        return SELFBUILDER_READXMLERR;
    }
    return SELFBUILDER_SUCCESS;
}

bool SelfBuilder::createNewModeName(const QString &path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString str;
        str = in.readLine();
        qDebug()<<"count"<<str;
        file.close();
        int num = str.toInt();
        num++;
        QString newStr = QString::number(num);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out<<newStr<<endl;
        m_modeName = "SD" + QString::number(m_axisNum) + "_New" + str;
        file.close();
        return true;
    } else {
        qDebug()<<"open file error";
        return false;
    }
}

bool SelfBuilder::axisNumExisted(const QString &num, const QString &path)
{
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        return false;
    }
    for (int i = tree->topLevelItemCount() - 1; i >= 0; i--) {
        QTreeWidgetItem *item = tree->topLevelItem(i);
        if (item->text(IDMAP_AXISNUM).compare(num) == 0) {
            m_newestID = item->text(IDMAP_ID);
            m_newestMode = item->text(IDMAP_MODE);
            m_newestType = item->text(IDMAP_TYPE);
            delete tree;
            return true;
        }
    }
    delete tree;
    return false;
}

QString SelfBuilder::getNewestVersion(const QString &path)
{
    QDir dir(path);
    if (!dir.exists()) {
        return "";
    }
    dir.setFilter(QDir::Dirs);
    QFileInfoList list = dir.entryInfoList();
    int max = 0;
    int ver = 0;
    for (int i = 0; i < list.count(); i++) {
        QFileInfo fileInfo = list.at(i);
        QString dirName = fileInfo.baseName();
        ver = dirName.right(dirName.length() - 1).toInt();
        if (ver > max) {
            max = ver;
        }
    }
    QString version = "V" + QString::number(max);
    return version;
}

bool SelfBuilder::createNewNode(const QString &path, const QString &id)
{
    QTreeWidget *powerMap = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (powerMap == NULL) {
        return false;
    }
    QStringList nameList;
    nameList<<id<<m_typeName<<m_modeName<<"nick"<<QString::number(m_axisNum);
    powerMap->addTopLevelItem(new QTreeWidgetItem(nameList));
    return true;
}

bool SelfBuilder::createSysPath(const QString &path)
{
    QDir dir(path);
    if (dir.exists()) {
        return true;
    }
    else {
        bool ok = dir.mkpath(path);
        return ok;
    }
}

bool SelfBuilder::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    if (sourceDir == toDir) {
        return true;
    }
    if (!QFile::exists(sourceDir)) {
        return false;
    }
    QDir *createfile = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist) {
        if(coverFileIfExist) {
            createfile->remove(toDir);
        }
    }
    if(!QFile::copy(sourceDir, toDir)) {
        qDebug()<<"copy fail";
        return false;
    }
    return true;
}

bool SelfBuilder::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){
        if(!createSysPath(toDir)) {
            return false;
        }
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    for (int i = 0; i < fileInfoList.count(); i++){
        QFileInfo fileInfo = fileInfoList.at(i);
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;
        if(fileInfo.isDir()){
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist)) {
                return false;
            }
        }
        else{
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
                targetDir.remove(fileInfo.fileName());
            }
            if(!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))) {
                return false;
            }
        }
    }
    return true;
}
