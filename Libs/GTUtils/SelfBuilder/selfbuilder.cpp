#include "gtutils.h"
#include "qttreemanager.h"
#include "selfbuilder.h"
#include "sdtglobaldef.h"
#include "sdterror.h"

#include <QFile>
#include <QTextStream>
#include <QTreeWidget>
#include <QDebug>
#include <QDir>
#include <QByteArray>
#include <QMessageBox>

using namespace ComDriver;

class SelfBuilderPrivate {
public:
    QString m_modeName;
    QString m_typeName;
    int m_axisNum;
    QString m_product;
    QString m_series;
    QString m_powerID;
    QString m_controlID;
    QString m_version;
    ComDriver::ICom *m_com;
    ComDriver::IComType m_type;
    QString m_newestMode;
    QString m_newestType;
    QString m_newestID;
    QString m_newestVersion;
    bool m_modeCreated;
    int m_count;
    int m_pwrBaseAddr;
    int m_ctrBaseAddr;
};

SelfBuilder::SelfBuilder(ComDriver::ICom *com)
{
    dd = new SelfBuilderPrivate;
    dd->m_com = com;
    dd->m_type = dd->m_com->iComType();;
    //dd->m_type = ICOM_TYPE_RNNET;
}

SelfBuilder::RtnSelf SelfBuilder::buildFromEprom(void (*processCallback)(void *pbar,short *value),void *processbar, BuilderParameters *parameters)
{
    dd->m_powerID = QString::number(parameters->m_pwrId);
    dd->m_controlID = QString::number(parameters->m_ctrId);
    dd->m_version = parameters->m_version;
    RtnSelf rtn;
    rtn = initParameters();
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    rtn = buildPower(processCallback, processbar);
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    rtn = buildControl();
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::buildPower(void (*processCallback)(void *pbar,short *value),void *processbar)
{
    emit sendProcessInfo(0, tr("Building new power board"));
    QString boardPath = GTUtils::databasePath() + "Board/PB/";
    QString indexPath = boardPath + "pbindex.ui";
    QString pwrMapPath = boardPath + "IdMap_Power.ui";
    QString selectPath = GTUtils::sysPath() + "SysMap/ConfigSelectTree.ui";
    QString databaseSelPath = GTUtils::databasePath() + "Board/SelectTree.ui";
    RtnSelf rtn;
    emit sendProcessInfo(5, tr("Checking axis number"));
    if (!axisNumExisted(QString::number(dd->m_axisNum), pwrMapPath)) {
        qDebug()<<"no such product";
        //SdtError::instance()->errorStringList()->append(tr("No such product. Please update the software."));
        return RTN_SELF_NOPRODUCT;
    }
    if (!idExisted(dd->m_powerID, pwrMapPath)) {
        //pwrID nonexist
//        emit sendProcessInfo(10, tr("Updating IdMap"));
//        rtn = addModeToIdMap(dd->m_powerID, pwrMapPath);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(12, tr("Updating database"));
//        rtn = addNewDatabase(dd->m_powerID, boardPath, indexPath);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(25, tr("Updating index tree"));
//        rtn = addIndexTree(indexPath, dd->m_powerID);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(30, tr("Updating select tree"));
//        rtn = addSelectTree(selectPath, dd->m_powerID);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(35, tr("Updating select tree"));
//        rtn = addDatabaseSelectTree(databaseSelPath);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(40, tr("Updating system config"));
//        rtn = addSysConfig(processCallback, processbar);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(50, tr("Updating system map"));
//        rtn = addSystemMap();
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
        qDebug()<<"no power id";
        //SdtError::instance()->errorStringList()->append(tr("your software is too old ,not support the current device\nplease update from\n\nhttp://www.googoltech.com.cn\n"));
        return RTN_SELF_IDNONEXIST;
    } else if (!versionExisted(dd->m_version, selectPath)) {
        //pwrID exist while version nonexist
        emit sendProcessInfo(10, tr("Updating database version"));
        rtn = addDatabaseVersion(dd->m_powerID, boardPath);
        if (rtn != RTN_SELF_SUCCESS) {
            return rtn;
        }
        emit sendProcessInfo(15, tr("Updating select tree"));
        rtn = addSelectTree(selectPath, dd->m_powerID);
        if (rtn != RTN_SELF_SUCCESS) {
            return rtn;
        }
        emit sendProcessInfo(20, tr("Updating system config"));
        rtn = addSysConfig(processCallback, processbar);
        if (rtn != RTN_SELF_SUCCESS) {
            return rtn;
        }
        emit sendProcessInfo(45, tr("Updating system map"));
        rtn = addSystemMap();
        if (rtn != RTN_SELF_SUCCESS) {
            return rtn;
        }
    }
    return RTN_SELF_SUCCESS;
}



SelfBuilder::RtnSelf SelfBuilder::buildControl()
{
    emit sendProcessInfo(50, tr("Building new control board"));
    QString boardPath = GTUtils::databasePath() + "Board/CB/";
    QString indexPath = boardPath + "cbindex.ui";
    QString ctrMapPath = boardPath + "IdMap_Control.ui";
    RtnSelf rtn;
    emit sendProcessInfo(55, tr("Checking axis number"));
    if (!axisNumExisted(QString::number(dd->m_axisNum), ctrMapPath)) {
        qDebug()<<"no such product";
        //SdtError::instance()->errorStringList()->append(tr("No such product. Please update the software."));
        return RTN_SELF_NOPRODUCT;
    }
    if (!idExisted(dd->m_controlID, ctrMapPath)) {
        //pwrID nonexist
//        emit sendProcessInfo(60, tr("Updating Id Map"));
//        rtn = addModeToIdMap(dd->m_controlID, ctrMapPath);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(70, tr("Updating database"));
//        rtn = addNewCtrDatabase(dd->m_controlID, boardPath, indexPath);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
//        emit sendProcessInfo(95, tr("Updating index tree"));
//        rtn = addIndexTree(indexPath, dd->m_controlID);
//        if (rtn != RTN_SELF_SUCCESS) {
//            return rtn;
//        }
        qDebug()<<"no control id";
        //SdtError::instance()->errorStringList()->append(tr("your software is too old ,not support the current device\nplease update from\n\nhttp://www.googoltech.com.cn\n"));
        return RTN_SELF_IDNONEXIST;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::initParameters()
{
    // read axisNum, product type, series num from hardware
    QString boardPath = GTUtils::databasePath() + "Board/PB/";
    QString indexPath = boardPath + "pbindex.ui";
    dd->m_pwrBaseAddr = getBaseAddress(indexPath);
    qDebug()<<"pwrBaseAdd"<<dd->m_pwrBaseAddr;
    boardPath = GTUtils::databasePath() + "Board/CB/";
    indexPath = boardPath + "cbindex.ui";
    dd->m_ctrBaseAddr = getBaseAddress(indexPath);
    qDebug()<<"ctrBaseAdd"<<dd->m_ctrBaseAddr;
    uint16_t ofst = 1 + dd->m_pwrBaseAddr;
    uint8_t value[4];
    uint16_t num = 2;
    uint8_t cs = 0;
    errcode_t ret;
    ret = dd->m_com->readEEPROM(ofst, value, num, cs);
    if (ret != 0) {
        return RTN_SELF_READPRODUCTERR;
    }
    QByteArray tempByte;
    tempByte.append(value[0]);
    if (value[1] != 0) {
        tempByte.append(value[1]);
    }
    dd->m_product = QString::fromLatin1(tempByte);

    ofst = 3 + dd->m_pwrBaseAddr;
    ret = dd->m_com->readEEPROM(ofst, value, num, cs);
    if (ret != 0) {
        return RTN_SELF_READAXISERR;
    }
    double tempValue = 0;
    for (int j = 0; j < num; j++) {
        tempValue = tempValue + (value[j] << (j * 8));
    }
    dd->m_axisNum = tempValue;

    ofst = 5 + dd->m_pwrBaseAddr;
    ret = dd->m_com->readEEPROM(ofst, value, num, cs);
    if (ret != 0) {
        return RTN_SELF_READSERIESERR;
    }
    tempValue = 0;
    for (int j = 0; j < num; j++) {
        tempValue = tempValue + (value[j] << (j * 8));
    }
    dd->m_series = QString::number(tempValue);

//    m_product = "M";
//    m_axisNum = 6;
//    m_series = "1";

    dd->m_modeCreated = false;
    dd->m_count = 0;
    return RTN_SELF_SUCCESS;
}

bool SelfBuilder::idExisted(const QString &id, const QString &path)
{
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        return false;
    }
    QTreeWidgetItem* item = GTUtils::findItem(id, tree, GT::COL_IDMAP_ID);
    if (item == NULL) {
        delete tree;
        return false;
    }
    dd->m_typeName = item->text(GT::COL_IDMAP_TYPE);
    dd->m_modeName = item->text(GT::COL_IDMAP_MODE);
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
    if (dd->m_type == ICOM_TYPE_PCDEBUG) {
        type = "PcDebug";
    } else if (dd->m_type == ICOM_TYPE_RNNET) {
        type = "RnNet";
    }
    QTreeWidgetItem *comItem = GTUtils::findItem(type, tree, GT::COL_CONFIG_NAME);
    if (comItem == NULL) {
        qDebug()<<"com type non-exist";
        return false;
    }
    QTreeWidgetItem *typeItem = GTUtils::findItemInItem(dd->m_typeName, comItem, GT::COL_CONFIG_NAME);
    if (typeItem == NULL) {
        qDebug()<<"type name non-exist";
        return false;
    }
    QTreeWidgetItem *modeItem = GTUtils::findItemInItem(dd->m_modeName, typeItem, GT::COL_CONFIG_NAME);
    if (modeItem == NULL) {
        qDebug()<<"mode name non-exist";
        return false;
    }
    QTreeWidgetItem *versionItem = GTUtils::findItemInItem(ver, modeItem, GT::COL_CONFIG_NAME);
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

SelfBuilder::RtnSelf SelfBuilder::addModeToIdMap(const QString &id, const QString &path)
{
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        return RTN_SELF_CREATETREEERR;
    }
    bool ok;
    if (!dd->m_modeCreated) {
        dd->m_typeName = "SD" + QString::number(dd->m_axisNum) +"x";
        QString filePath = GTUtils::sysPath() + dd->m_typeName + "/Index.ini";
        ok = createNewModeName(filePath);
        if (!ok) {
            delete tree;
            return RTN_SELF_NEWMODEERR;
        }
        dd->m_modeCreated = true;
    }
    QStringList list;
    list<<id<<dd->m_typeName<<dd->m_modeName<<"nick"<<QString::number(dd->m_axisNum);
    tree->addTopLevelItem(new QTreeWidgetItem(list));
    ok = QtTreeManager::writeTreeWidgetToXmlFile(path, tree);
    delete tree;
    if (!ok) {
        return RTN_SELF_WRITETREEERR;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addNewDatabase(const QString &id, const QString &path, const QString &indexPath) {
    QString idPath = path + dd->m_product + "/" + dd->m_product + QString::number(dd->m_axisNum) +
                     "/series" + dd->m_series + "/" + id +"/";
    QString versionPath = idPath + "filter/" + dd->m_version + "/";
    QString oldIdPath = path + getOldPath(indexPath);
    dd->m_newestVersion = getNewestVersion(oldIdPath + "filter/");
    QString oldVersionPath = oldIdPath + "filter/" + dd->m_newestVersion + "/";

    bool ok = createSysPath(versionPath);
    if (!ok) {
        return RTN_SELF_CREATEPATHERR;
    }
    ok = copyFileToPath(oldIdPath + dd->m_newestID + ".ui", idPath + id + ".ui", false);
    if (!ok) {
        return RTN_SELF_COPYERR;
    }
    ok = copyFileToPath(oldVersionPath + dd->m_newestVersion + ".ui", versionPath + dd->m_version + ".ui", false);
    if (!ok) {
        return RTN_SELF_COPYERR;
    }
    RtnSelf rtn = readDataFromEEprom(idPath + id + ".ui", true);
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addNewCtrDatabase(const QString &id, const QString &path, const QString &indexPath)
{
    QString idPath = path + dd->m_product + "/" + dd->m_product + QString::number(dd->m_axisNum) +
                     "/series" + dd->m_series + "/" + id +"/";
    QString oldIdPath = path + getOldPath(indexPath);
    bool ok = createSysPath(idPath);
    if (!ok) {
        return RTN_SELF_CREATEPATHERR;
    }
    ok = copyFileToPath(oldIdPath + dd->m_newestID + ".ui", idPath + id + ".ui", false);
    if (!ok) {
        return RTN_SELF_COPYERR;
    }
    RtnSelf rtn = readDataFromEEprom(idPath + id + ".ui", false);
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addIndexTree(const QString &path, const QString &id)
{
    QTreeWidget* indexTree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (indexTree == NULL) {
        return RTN_SELF_CREATETREEERR;
    }
    QTreeWidgetItem* basicItem = indexTree->topLevelItem(1);
    QStringList list;
    list<<dd->m_product<<dd->m_product;
    QTreeWidgetItem* item = addBasicChild(basicItem, list);
    list.clear();
    list<<dd->m_product + QString::number(dd->m_axisNum)<<QString::number(dd->m_axisNum);
    QTreeWidgetItem* item_1 = addBasicChild(item, list);
    list.clear();
    list<<"series" + dd->m_series<<dd->m_series;
    QTreeWidgetItem* item_2 = addBasicChild(item_1, list);
    list.clear();
    list<<"Nick"<<id;
    addBasicChild(item_2, list);
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, indexTree);
    delete indexTree;
    if (!ok) {
        return RTN_SELF_WRITETREEERR;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addSelectTree(const QString &path, const QString &id)
{
    QTreeWidget *selectTree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (selectTree == NULL) {
        return RTN_SELF_CREATETREEERR;
    }
    QTreeWidgetItem* basicItem;
    if (dd->m_type == ICOM_TYPE_PCDEBUG) {
        basicItem = selectTree->topLevelItem(0);
    } else if (dd->m_type == ICOM_TYPE_RNNET) {
        basicItem = selectTree->topLevelItem(1);
    }
    QStringList list;
    list<<dd->m_typeName<<QString::number(dd->m_axisNum)<<""<<"";
    QTreeWidgetItem* item = addBasicChild(basicItem, list);
    list.clear();
    list<<dd->m_modeName<<QString::number(dd->m_axisNum)<<id<<"";
    QTreeWidgetItem* item_1 = addBasicChild(item, list);
    list.clear();
    list<<dd->m_version<<"NULL"<<"0"<<"";
    addBasicChild(item_1, list);
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, selectTree);
    delete selectTree;
    if (!ok) {
        return RTN_SELF_WRITETREEERR;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addDatabaseSelectTree(const QString &path)
{
    QTreeWidget *selectTree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (selectTree == NULL) {
        return RTN_SELF_CREATETREEERR;
    }
    QTreeWidgetItem* basicItem = selectTree->invisibleRootItem();
    QStringList list;
    list<<dd->m_typeName<<"";
    QTreeWidgetItem* item = addBasicChild(basicItem, list);
    list.clear();
    list<<dd->m_modeName<<QString::number(dd->m_axisNum / 2);
    addBasicChild(item, list);
    list.clear();
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, selectTree);
    delete selectTree;
    if (!ok) {
        return RTN_SELF_WRITETREEERR;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addSysConfig(void (*processCallback)(void *pbar,short *value),void *processbar)
{
    QString toDir = GTUtils::sysPath() + dd->m_typeName + "/" + dd->m_modeName + "/" + dd->m_version + "/";
    QString fromDir = GTUtils::sysPath() + dd->m_newestType + "/" + dd->m_newestMode + "/" + dd->m_newestVersion + "/";
    bool ok = copyDirectoryFiles(fromDir, toDir, true);
    if (!ok) {
        return RTN_SELF_COPYERR;
    }
    //use huanglian's interface to deal with the xml documents
    RtnSelf rtn = changeDocuments(processCallback, processbar, toDir);
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addSystemMap()
{
    QString comType;
    if (dd->m_type == ICOM_TYPE_PCDEBUG) {
        comType = "PcDebug";
    } else if (dd->m_type == ICOM_TYPE_RNNET) {
        comType = "RnNet";
    }
    QString tempDir = GTUtils::sysPath() + "SysMap/" + comType + "/" + dd->m_typeName + "/" + dd->m_modeName + "/" + dd->m_version + "/";
    QString toDir = tempDir + "TargetTree.ui";
    QString fromDir = GTUtils::sysPath() + "SysMap/" + comType + "/" + dd->m_newestType + "/" + dd->m_newestMode + "/" + dd->m_newestVersion + "/TargetTree.ui";
    bool ok = createSysPath(tempDir);
    if (!ok) {
        return RTN_SELF_CREATEPATHERR;
    }
    ok = copyFileToPath(fromDir, toDir, true);
    if (!ok) {
        return RTN_SELF_COPYERR;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::addDatabaseVersion(const QString &id, const QString &path)
{
    QString idPath = path + dd->m_product + "/" + dd->m_product + QString::number(dd->m_axisNum) +
                     "/series" + dd->m_series + "/" + id +"/";
    QString versionPath = idPath + "filter/" + dd->m_version + "/";
    dd->m_newestVersion = getNewestVersion(idPath + "filter/");
    QString oldVersionPath = idPath + "filter/" + dd->m_newestVersion + "/";
    bool ok = createSysPath(versionPath);
    if (!ok) {
        return RTN_SELF_CREATEPATHERR;
    }
    ok = copyFileToPath(oldVersionPath + dd->m_newestVersion + ".ui", versionPath + dd->m_version + ".ui", false);
    if (!ok) {
        return RTN_SELF_COPYERR;
    }
    return RTN_SELF_SUCCESS;
}

QTreeWidgetItem* SelfBuilder::addBasicChild(QTreeWidgetItem *item, const QStringList &list)
{
    for (int i = 0; i < item->childCount(); i++) {
        if (item->child(i)->text(GT::COL_INDEX_NAME).compare(list.at(0)) == 0) {
            return item->child(i);
        }
    }
    item->addChild(new QTreeWidgetItem(list));
    return item->child(item->childCount() - 1);
}

QString SelfBuilder::getOldPath(const QString &indexPath)
{
    QTreeWidget* indexTree = QtTreeManager::createTreeWidgetFromXmlFile(indexPath);
    QTreeWidgetItem *newestItem = GTUtils::findItem(dd->m_newestID, indexTree, GT::COL_INDEX_NAME);
    QString result = dd->m_newestID + "/";
    int count = 0;
    QTreeWidgetItem *currentItem = newestItem;
    while (count < 3) {
        currentItem = currentItem->parent();
        result = currentItem->text(GT::COL_INDEX_NAME) + "/" + result;
        count++;
    }
    delete indexTree;
    return result;
}

SelfBuilder::RtnSelf SelfBuilder::readDataFromEEprom(const QString &path, bool isPwr)
{
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(path);
    if (tree == NULL) {
        return RTN_SELF_CREATETREEERR;
    }
    QTreeWidgetItem *codeItem = tree->topLevelItem(1)->child(0)->child(0)->child(0)->child(0);
    codeItem->setText(GT::COL_BOARDTREE_NAME, dd->m_modeName);
    if (isPwr) {
        codeItem->setText(GT::COL_BOARDTREE_VALUE, dd->m_powerID);
    } else {
        codeItem->setText(GT::COL_BOARDTREE_VALUE, dd->m_controlID);
    }
    RtnSelf rtn = readTreeData(tree->invisibleRootItem(), isPwr);
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    bool ok = QtTreeManager::writeTreeWidgetToXmlFile(path, tree);
    delete tree;
    if (!ok) {
        return RTN_SELF_WRITETREEERR;
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::readTreeData(QTreeWidgetItem *item, bool isPwr)
{
    dd->m_count++;
    if (dd->m_count % 5 == 0) {
        emit sendProcessInfo(dd->m_count % 100, tr("Updating database"));
    }
    RtnSelf rtn;
    rtn = readSingle(item, isPwr);
    if (rtn != RTN_SELF_SUCCESS) {
        return rtn;
    }
    if (item->text(GT::COL_BOARDTREE_TYPE).compare("Case") == 0) {
        int index = item->text(GT::COL_BOARDTREE_VALUE).toInt();
        rtn = readTreeData(item->child(index), isPwr);
        if (rtn != RTN_SELF_SUCCESS) {
            return rtn;
        }
    } else {
        for (int i = 0; i < item->childCount(); i++) {
            rtn = readTreeData(item->child(i), isPwr);
            if (rtn != RTN_SELF_SUCCESS) {
                return rtn;
            }
        }
    }
    return RTN_SELF_SUCCESS;
}

SelfBuilder::RtnSelf SelfBuilder::changeDocuments(void (*processCallback)(void *, short *), void *processbar, const QString &path)
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
    errcode_t ret = dd->m_com->readXML(axis, pFileNameList, pFileTypeList, num, processCallback, processbar, count);
    qDebug()<<"ret"<<ret;
    for (int i = 0; i < num; i++)
    {
        free(pFileNameList[i]);
    }
    if (ret != 0) {
        return RTN_SELF_READXMLERR;
    }
    return RTN_SELF_SUCCESS;
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
        dd->m_modeName = "SD" + QString::number(dd->m_axisNum) + "_New" + str;
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
        if (item->text(GT::COL_IDMAP_AXISNUM).compare(num) == 0) {
            dd->m_newestID = item->text(GT::COL_IDMAP_ID);
            dd->m_newestMode = item->text(GT::COL_IDMAP_MODE);
            dd->m_newestType = item->text(GT::COL_IDMAP_TYPE);
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
    nameList<<id<<dd->m_typeName<<dd->m_modeName<<"nick"<<QString::number(dd->m_axisNum);
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

int SelfBuilder::getBaseAddress(const QString indexPath)
{
    QTreeWidget* indexTree = QtTreeManager::createTreeWidgetFromXmlFile(indexPath);
    QTreeWidgetItem *xmlBaseAdd;
    bool ok;
    xmlBaseAdd = GTUtils::findItem("xmlBaseAddress", indexTree, GT::COL_INDEX_NAME);
    int baseAdd = xmlBaseAdd->text(GT::COL_INDEX_VALUE).toInt(&ok, 10);
    delete indexTree;
    return baseAdd;
}

SelfBuilder::RtnSelf SelfBuilder::readSingle(QTreeWidgetItem *item, bool isPwr)
{
    if (item->text(GT::COL_BOARDTREE_ADDRESS).compare("0x0001") == 0) {
        item->setText(GT::COL_BOARDTREE_VALUE, dd->m_product);
    } else if (item->text(GT::COL_BOARDTREE_ADDRESS).compare("0x0003") == 0) {
        item->setText(GT::COL_BOARDTREE_VALUE, QString::number(dd->m_axisNum));
    } else if (item->text(GT::COL_BOARDTREE_ADDRESS).compare("0x0005") == 0) {
        item->setText(GT::COL_BOARDTREE_VALUE, dd->m_series);
    } else if (item->text(GT::COL_BOARDTREE_ADDRESS).compare("-1") != 0 && item->text(GT::COL_BOARDTREE_ADDRESS).compare("") != 0) {
        bool ok;
        uint16_t ofst = item->text(GT::COL_BOARDTREE_ADDRESS).toUShort(&ok, 16);
        uint8_t value[4];
        QString numType = item->text(GT::COL_BOARDTREE_TYPE);
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
            ofst = ofst + dd->m_pwrBaseAddr;
        } else {
            cs = 1;
            ofst = ofst + dd->m_ctrBaseAddr;
        }
        errcode_t ret = dd->m_com->readEEPROM(ofst, value, num, cs);
        if (ret != 0) {
            return RTN_SELF_READTREEERR;
        }
        double tempValue = 0;
        double scale = item->text(GT::COL_BOARDTREE_SCALE).toDouble();
        for (int j = 0; j < num; j++) {
            tempValue = tempValue + (value[j] << (j * 8));
        }
        if (numType.compare("int8") == 0) {
            int8_t tempValueTwo = tempValue;
            item->setText(GT::COL_BOARDTREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
        } else if (numType.compare("int16") == 0) {
            int16_t tempValueTwo = tempValue;
            item->setText(GT::COL_BOARDTREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
        } else if (numType.compare("int32") == 0) {
            int32_t tempValueTwo = tempValue;
            item->setText(GT::COL_BOARDTREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
        } else {
            item->setText(GT::COL_BOARDTREE_VALUE, QString::number(tempValue / scale, 'g', 8));
        }
    }
    return RTN_SELF_SUCCESS;
}
