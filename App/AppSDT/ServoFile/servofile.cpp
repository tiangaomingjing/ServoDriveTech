#include "servofile.h"
#include "sevdevice.h"
#include "qttreemanager.h"
#include "gtutils.h"
#include "sdtglobaldef.h"
#include "advusercheck.h"
#include "optuser.h"
#include "optcontainer.h"
#include "advusercontainer.h"

#include <QMessageBox>
#include <QApplication>
#include <QDebug>

#define XMLFILE_ROW_INDEX 0
#define XMLFILE_CHILD_VERSION_ROW_INDEX 0
#define XMLFILE_NODE_NAME "XmlFileInformation"

ServoFile::ServoFile(QObject *parent) :  QObject(parent)
{

}


bool ServoFile::downLoadFile(void (*processCallback)(void *pbar,short *value), void *processbar, const QString &xmlPath, SevDevice *dev)
{
    QTreeWidget* downloadTree = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    m_downloadItemNum = getItemNum(downloadTree);
    if (downloadTree == NULL) {
        QMessageBox::information(0, tr("Warning"), tr("Xml file error!"));
        return false;
    }
    quint16 dspVersion;
    qint16 err = dev->socketCom()->readDSPVersion(0, dspVersion);
    if (err != 0) {
        QMessageBox::information(0, tr("Error"), tr("Read dsp version error!"));
        delete downloadTree;
        return false;
    }
    qDebug()<<"dsp version"<<dspVersion;
    QString dspPath = GTUtils::sysPath() + dev->typeName() + "/" + dev->modelName() + "/V" + QString::number(dspVersion) + "/";
    qDebug()<<"dspPath"<<dspPath;
    QDir dir(dspPath);
    if (!dir.exists()) {
        QString prmPath = GTUtils::sysPath() + dev->typeName() + "/" + dev->modelName() + "/" + dev->versionName() + "/prm/V" + QString::number(dspVersion) + "/";
        QDir prmDir(prmPath);
        if (!prmDir.exists()) {
            prmDir.mkdir(prmPath);
        }
        emit sendProgressbarMsg(0, tr("Reading Xml Files"));
        bool ok = readXmlFromDsp(processCallback, (void*)processbar, prmPath, dev);
        if (!ok) {
            QMessageBox::information(0, tr("Error"), tr("Read xml file Error!"));
            bool delOk = deleteDir(prmPath);
            qDebug()<<"delOk"<<delOk;
            return false;
        }
        dspPath = prmPath;
    }
    QString xmlNodeName = downloadTree->topLevelItem(XMLFILE_ROW_INDEX)->text(GT::COL_FLASH_ALLAXIS_NAME);
    quint16 xmlVersion;
    if (xmlNodeName.compare(XMLFILE_NODE_NAME) == 0) {
        QTreeWidgetItem *versionNodeItem;
        xmlVersion = downloadTree->topLevelItem(XMLFILE_ROW_INDEX)->child(XMLFILE_CHILD_VERSION_ROW_INDEX)->text(GT::COL_FLASH_RAM_TREE_VALUE).toUInt();
        versionNodeItem = downloadTree->takeTopLevelItem(XMLFILE_ROW_INDEX);
        delete versionNodeItem;
    } else {
        xmlVersion = 0;
    }
    qDebug()<<"xml version"<<xmlVersion;
    if (downloadTree->topLevelItemCount() != dev->axisNum()) {
        QString msg = tr("axis number of current xml file is not equal to the device");
        QMessageBox::information(0, tr("Warning"), msg);
        downloadTree->clear();
        delete downloadTree;
        return false;
    }
    connect(dev, SIGNAL(initProgressInfo(int,QString)), this, SIGNAL(sendProgressbarMsg(int,QString)));
    OptUser *user = dynamic_cast<OptUser *>(OptContainer::instance()->optItem("optuser"));
    AdvUserCheck *usrCheck = dynamic_cast<AdvUserCheck *>(AdvUserContainer::instance()->advItem("advusercheck"));
    bool isAdmin = user->isAdmin();
    bool isChecked = usrCheck->isChecked();
    bool isOk;
    if (!isAdmin || (isAdmin && isChecked)) {
        isOk = dev->checkLoadParameters(downloadTree, m_downloadItemNum);
    }
    disconnect(dev, SIGNAL(initProgressInfo(int,QString)), this, SIGNAL(sendProgressbarMsg(int,QString)));
    if (!isOk) {
        delete downloadTree;
        return false;
    }
    if (xmlVersion != dspVersion) {
        QString dspFilePath = dspPath + FLASH_ALL_PRM_NAME;
        QTreeWidget* dspTree = QtTreeManager::createTreeWidgetFromXmlFile(dspFilePath);
        m_barCount = 0;
        updatePrmTreeItem(downloadTree->invisibleRootItem(), dspTree->invisibleRootItem());
        if (dspTree->topLevelItem(XMLFILE_ROW_INDEX)->text(GT::COL_FLASH_ALLAXIS_NAME).compare(XMLFILE_NODE_NAME) == 0) {
            QTreeWidgetItem *versionNodeItem;
            versionNodeItem = dspTree->takeTopLevelItem(XMLFILE_ROW_INDEX);
            delete versionNodeItem;
        }
        m_barCount = 0;
        for (int i = 0; i < dspTree->topLevelItemCount(); i++) {
            bool ok = downloadItem(dev, i, dspTree->topLevelItem(i));
            if (!ok) {
                return false;
            }
        }
        delete dspTree;
    } else {
        m_barCount = 0;
        for (int i = 0; i < downloadTree->topLevelItemCount(); i++) {
            bool ok = downloadItem(dev, i, downloadTree->topLevelItem(i));
            if (!ok) {
                return false;
            }
        }
    }
    delete downloadTree;
    return true;
}

bool ServoFile::upLoadFile(void (*processCallback)(void *pbar,short *value), void *processbar, const QString &xmlPath, SevDevice *dev)
{
    m_barCount = 0;
    quint16 dspVersion;
    qint16 err = dev->socketCom()->readDSPVersion(0, dspVersion);
    if (err != 0) {
        QMessageBox::information(0, tr("Error"), tr("Read dsp version error!"));
        return false;
    }
    qDebug()<<"dsp version"<<dspVersion;
    QString dspPath = GTUtils::sysPath() + dev->typeName() + "/" + dev->modelName() + "/V" + QString::number(dspVersion) + "/";
    QDir dir(dspPath);
    if (!dir.exists()) {
        QString prmPath = GTUtils::sysPath() + dev->typeName() + "/" + dev->modelName() + "/" + dev->versionName() + "/prm/V" + QString::number(dspVersion);
        QDir prmDir(prmPath);
        if (!prmDir.exists()) {
            prmDir.mkdir(prmPath);
        }
        emit sendProgressbarMsg(0, tr("Reading Xml Files"));
        bool ok = readXmlFromDsp(processCallback, (void*)processbar, prmPath, dev);
        if (!ok) {
           QMessageBox::information(0, tr("Error"), tr("Read xml file Error!"));
           bool delOk = deleteDir(prmPath);
           qDebug()<<"delOk"<<delOk;
           return false;
        }
        dspPath = prmPath;
    }
    qDebug()<<"dsp path"<<dspPath;
    QString dspFilePath = dspPath + FLASH_ALL_PRM_NAME;
    QTreeWidget* dspTree = QtTreeManager::createTreeWidgetFromXmlFile(dspFilePath);
    QString xmlNodeName = dspTree->topLevelItem(XMLFILE_ROW_INDEX)->text(GT::COL_FLASH_RAM_TREE_NAME);
    m_uploadItemNum = getItemNum(dspTree);
    QTreeWidgetItem* versionNodeItem = NULL;
    if (xmlNodeName.compare(XMLFILE_NODE_NAME) == 0) {
        versionNodeItem = dspTree->takeTopLevelItem(XMLFILE_ROW_INDEX);
    }
    qDebug()<<"xmlNodeName"<<xmlNodeName;
    for (int i = 0; i < dspTree->topLevelItemCount(); i++) {
        bool ok = uploadItem(dev, i, dspTree->topLevelItem(i));
        if (!ok) {
            return false;
        }
    }
    qDebug()<<"a";
    if (versionNodeItem != NULL) {
        qDebug()<<"insert";
        dspTree->insertTopLevelItem(XMLFILE_ROW_INDEX, versionNodeItem);
    }
    qDebug()<<"b";
    QtTreeManager::writeTreeWidgetToXmlFile(xmlPath, dspTree);
    qDebug()<<"c";
    delete dspTree;
    return true;
}

//void ServoFile::updatePrmTree(QTreeWidget *downloadTree, QTreeWidget *dspTree)
//{
//    m_barCount = 0;
//    for (int i = 0; i < downloadTree->topLevelItemCount(); i++) {
//        updatePrmTreeItem(downloadTree->invisibleRootItem(), dspTree->invisibleRootItem());
//    }
//}

void ServoFile::updatePrmTreeItem(QTreeWidgetItem *downloadItem, QTreeWidgetItem *dspItem)
{
    m_barCount++;
    if (m_barCount % 10 == 0) {
        qApp->processEvents();
        emit sendProgressbarMsg(m_barCount * 100 / m_downloadItemNum, tr("Updating parameters"));
    }
    int sameIndex = -1;
    for (int i = 0; i < dspItem->childCount(); i++) {
        QString dspName = dspItem->child(i)->text(GT::COL_FLASH_RAM_TREE_NAME);
        for (int j = 0; j < downloadItem->childCount(); j++) {
            QString dowloadName = downloadItem->child(j)->text(GT::COL_FLASH_RAM_TREE_NAME);
            if (dspName.compare(dowloadName) == 0) {
                sameIndex = j;
                for (int k = 1; k < qMax(dspItem->columnCount(), downloadItem->columnCount()); k++) {
                    if (dspItem->child(i)->text(k).compare(downloadItem->child(j)->text(k)) != 0) {
                        dspItem->child(i)->setText(k, downloadItem->child(j)->text(k));
                    }
                }
                updatePrmTreeItem(downloadItem->child(j), dspItem->child(i));
                break;
            }
        }
    }
}

bool ServoFile::downloadItem(SevDevice *dev, int axisIndex, QTreeWidgetItem *item)
{
    m_barCount++;
    if (m_barCount % 10 == 0) {
        qApp->processEvents();
        emit sendProgressbarMsg(m_barCount * 100 / m_downloadItemNum, tr("Downloading axis%1").arg(QString::number(axisIndex + 1)) + item->text(GT::COL_FLASH_ALLAXIS_NAME));
    }
    if (item->text(GT::COL_FLASH_ALLAXIS_ADDR).compare("-1") != 0) {
        bool ok = dev->writePrmItemFlash(axisIndex, item);
        if (!ok) {
            QMessageBox::information(0, tr("Error"), tr("Download Error"));
            return false;
        }
    }
    for (int i = 0; i < item->childCount(); i++) {
        bool ok = downloadItem(dev, axisIndex, item->child(i));
        if (!ok) {
            return false;
        }
    }
    return true;
}

bool ServoFile::uploadItem(SevDevice *dev, int axisIndex, QTreeWidgetItem *item)
{
    m_barCount++;
    if (m_barCount % 10 == 0) {
        emit sendProgressbarMsg(m_barCount * 100 / m_uploadItemNum, tr("Uploading axis%1").arg(QString::number(axisIndex + 1)) + item->text(GT::COL_FLASH_ALLAXIS_NAME));
        qApp->processEvents();
    }
    if (item->text(GT::COL_FLASH_ALLAXIS_ADDR).compare("-1") != 0) {
        bool ok = dev->readPrmItemFlash(axisIndex, item);
        if (!ok) {
            QMessageBox::information(0, tr("Error"), tr("Upload Error"));
            return false;
        }
    }
    for (int i = 0; i < item->childCount(); i++) {
        bool ok = uploadItem(dev, axisIndex, item->child(i));
        if (!ok) {
            return false;
        }
    }
    return true;
}

bool ServoFile::readXmlFromDsp(void (*processCallback)(void *pbar, short *value), void *processbar, const QString &path, SevDevice* dev)
{
    QString path_allAxis = path + "FlashPrm_AllAxis.xml";
    QString path_axis0 = path + "PrmRAMAxis0.xml";
    QString path_axis1 = path + "PrmRAMAxis1.xml";
    if (isFileExist(path_allAxis) && isFileExist(path_axis0) && isFileExist(path_axis1)) {
        return true;
    }
    char* pFileNameList[3];
    int pFileTypeList[3];
    pFileTypeList[0] = 0;
    pFileTypeList[1] = 0;
    pFileTypeList[2] = 0;
    int num = 3;
    quint8 axis = 0;
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
    int ret = dev->socketCom()->readXML(axis, pFileNameList, pFileTypeList, num, processCallback, processbar, count);
    qDebug()<<"ret"<<ret;
    for (int i = 0; i < num; i++)
    {
        free(pFileNameList[i]);
    }
    if (ret != 0) {
        return false;
    }
    return true;
}

bool ServoFile::deleteDir(const QString &path)
{
    QDir dir(path);
    if (!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    bool ok;
    for (int i = 0; i < fileList.count(); i++) {
        QFileInfo file = fileList.at(i);
        ok = file.dir().remove(file.fileName());
        if (!ok) {
            return ok;
        }
    }
    ok = dir.rmdir(dir.absolutePath());
    return ok;
}

bool ServoFile::isFileExist(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

int ServoFile::getItemNum(QTreeWidget* tree)
{
    int count = 0;
    QTreeWidgetItemIterator it(tree);
    while (*it) {
        count++;
        ++it;
    }
    return count;
}
