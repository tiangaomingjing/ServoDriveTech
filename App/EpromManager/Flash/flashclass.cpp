#include "flashclass.h"
#include "jsonreader.h"
#include "ServoDriverComDll.h"
#include "treemanager.h"
#include "controlservo.h"
#include "globaldefine.h"
#include "gtutils.h"
#include "FolderCompressor/FolderCompressor.h"
#include <QProgressBar>
#include <QDir>

#define FILENAME_XML_FLASHPRM "FlashPrm_AllAxis.xml"
#define FILENAME_XML_RAMPRM0 "PrmRAMAxis0.xml"
#define FILENAME_XML_RAMPRM1 "PrmRAMAxis1.xml"

int FlashClass::m_progessValue = 0;
int FlashClass::m_dspNum = 2;
int FlashClass::m_step = 0;

FlashClass::FlashClass()
{
}

void FlashClass::updateProgessBarWhenRestoreClicked(void *arg, qint16 *value)
{
    QProgressBar *bar=static_cast<QProgressBar *>(arg);
    m_progessValue=(100/m_dspNum)*m_step+(*value)/m_dspNum;
    bar->setValue(m_progessValue);
    qApp->processEvents();
}

void FlashClass::onXmlPrmToServo(int value)
{
    emit changeBarCount(value);
}

void FlashClass::delayms(quint16 ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void FlashClass::flash(int netId, QString hexPath, QString xmlPath, int dspNum, bool hexChecked, bool rpdChecked, bool xmlChecked, QObject *proBar) {
    m_hexPath = hexPath;
    m_xmlPath = xmlPath;
    m_dspNum = dspNum;
    m_netId = netId;
    int axisCount = 0;
    QTreeWidget *treePrm = TreeManager::createTreeWidgetFromXmlFile(m_xmlPath);
    if (treePrm->topLevelItem(0)->text(0).compare("XmlFileInformation") == 0) {
        QTreeWidgetItem* tempItem = treePrm->takeTopLevelItem(0);
        delete tempItem;
        axisCount = treePrm->topLevelItemCount();
    } else {
        axisCount = treePrm->topLevelItemCount();
    }
    if (axisCount != 2 * m_dspNum) {
        emit sendWarnMsg(tr("Xml File Error! Please reselect file!"));
        return;
    }
    emit sendWarnMsg(tr("Uboot starting......"));
    JsonReader net;
    QString filePath = GTUtils::ubootPath() + "NetConfig.json";
    net.initialDataFromJsonFile(filePath);
    qint16 netRnStation = net.rnStation();
    m_netRnStation = netRnStation;
    QString outPath = GTUtils::ubootPath() + "ServoUboot.out";
    QString ldrPath = GTUtils::ubootPath() + "ServoUboot.ldr";
    emit sendWarnMsg(tr("Servo ubooting......"));
    if(0 == GTSD_CMD_Hex2Ldr(outPath.toStdWString(), ldrPath.toStdWString(), netId, netRnStation))//转化文件成功
    {

        bool ubootOk = uBoot(ldrPath, net, proBar);
        if (ubootOk)
        {
            bool ok;
            QString desPath = "./Decompress";
            QDir dir(desPath);
            if (dir.exists()) {
                deleteDir(desPath);
            }
            dir.mkdir(desPath);
            FolderCompressor *folderComp = new FolderCompressor(0);
            folderComp->decompressFolder(hexPath, desPath);
            if (hexChecked) {
                QStringList hexFilePath = getFilesFromExt("hex", desPath, 1);
                ok = downloadHex(proBar, hexFilePath.at(0));
                emit sendWarnMsg(tr("Download hex-file to servo complete!"));
                delayms(20);
            }
            if (!ok) {
                emit sendWarnMsg(tr("Download hex file error!"));
                deleteDir(desPath);
                return;
            }
            ControlServo scontrol;
            connect(&scontrol,SIGNAL(progressValue(int)),this,SLOT(onXmlPrmToServo(int)));
            emit sendWarnMsg(tr("Download xml parameters file to servo......"));
            delayms(20);
            emit changeBarCount(20);
            scontrol.writeServoFlashByAllAxisTree(treePrm,(COM_TYPE)netId,netRnStation);
            qDebug()<<"write file to servo complete";
            emit changeBarCount(60);
            delayms(20);
            treePrm->clear();
            delete treePrm;
            emit sendWarnMsg(tr("Download xml parameters file to servo complete successfully!"));

            if (xmlChecked) {
                emit sendWarnMsg(tr("Downloading xml files!"));
                ok = downloadXmlFiles(desPath, proBar);
            }
            if (!ok) {
                emit sendWarnMsg(tr("Download xml files fail!"));
                emit changeBarCount(0);
                deleteDir(desPath);
                return;
            }
            emit sendWarnMsg(tr("Flash successfully!"));
            m_progessValue = 0;
            m_step = 0;
            emit changeBarCount(0);
            deleteDir(desPath);
        }
        else
        {
            emit sendWarnMsg(tr("Uboot .out file error! Maybe you are not in the uboot or hardwares have some problems."));
        }
        emit changeBarCount(0);
    } else {
         emit sendWarnMsg(tr("Warning: Convert .out file to .ldr failed!"));
    }
}

bool FlashClass::uBoot(QString ldrPath, JsonReader net, QObject *proBar) {
    bool ubootOk = true;
    for(int i = 0; i < m_dspNum; i++)
    {
        m_step=i;
        if(0 != GTSD_CMD_ProcessorUartBootHandler(i*2,ldrPath.toStdWString(),\
                                              net.baudRate(), net.ubootCmd(),\
                                              net.ubootInputKey().toStdString(),\
                                              updateProgessBarWhenRestoreClicked,\
                                              proBar,m_netId,m_netRnStation))
        {
            sendWarnMsg(tr("Warning: Reasons of exceptions maybe  1.Boot Switch 2.FPGA FirmWare 3.Boot File"));
            ubootOk = false;
            break;
        } else {
            sendWarnMsg(tr("Uboot complete successfully!"));
        }
    }
    return ubootOk;
}

bool FlashClass::downloadHex(QObject *proBar, const QString &hexPath) {
    bool isHexDownload = false;
    int result = 0;
    for (int i = 0; i < m_dspNum; i++)
    {
        m_step = i;
        int axisNum = i + 1;
        emit sendWarnMsg(tr("Flashing DSP ") + QString("%1").arg(axisNum) + "!");
        result = GTSD_CMD_ProcessorFlashHandler(i * 2, hexPath.toStdWString(),updateProgessBarWhenRestoreClicked,(void*)proBar, m_netId, m_netRnStation);
        isHexDownload = true;
        if (result != 0)//hex没有烧写成功
        {
            isHexDownload=false;
            emit sendWarnMsg(tr("Error: download hex-file to servo not complete!"));
            break;
        }
    }
    return isHexDownload;
}

bool FlashClass::downloadXmlFiles(const QString &desPath, QObject* proBar)
{
    QStringList fileNameList;
    fileNameList.append(desPath + "/" + FILENAME_XML_FLASHPRM);
    fileNameList.append(desPath + "/" + FILENAME_XML_RAMPRM0);
    fileNameList.append(desPath + "/" + FILENAME_XML_RAMPRM1);
    QList<int> fileTypeList;
    fileTypeList<<0<<0<<0;

    int num = fileNameList.length();
    char** pFileNameList = new char*[num];
    int *pFileTypeList = new int[num];
    for (int i = 0; i < num; i++) {
        pFileTypeList[i] = fileTypeList.at(i);
        QString str = fileNameList.at(i);
        int size = str.length();
        char *p = (char *)malloc(size + 1);
        memset(p, 0, size + 1);
        memcpy_s(p, size, str.toStdString().c_str(), size);
        pFileNameList[i] = p;
    }
    quint8 axis = 0;
    short value = 60;
    short ret = GTSD_CMD_XmlWriteFile(axis, pFileNameList, pFileTypeList, num, processCallBack, proBar, value, m_netId, m_netRnStation);
    for (int i = 0; i < num; i++)
    {
        free(pFileNameList[i]);
    }
    if (ret != 0) {
        return false;
    }
    return true;
}

bool FlashClass::deleteDir(const QString &path)
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

QStringList FlashClass::getFilesFromExt(const QString &fileExt, const QString &filePath, int num)
{
    int count = 0;
    QStringList result;
    QDir dir(filePath);
    if (!dir.exists()){
        return result;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    for (int i = 0; i < fileList.count(); i++) {
        QFileInfo file = fileList.at(i);
        QString ext = file.suffix();
        if (ext.compare(fileExt) == 0) {
            count++;
            result.append(file.filePath());
        }
        if (count >= num) {
            break;
        }
    }
    return result;
}

void FlashClass::processCallBack(void *argv, short *value)
{
    QProgressBar *pBar = static_cast<QProgressBar *>(argv);
    pBar->setValue(*value);
    qApp->processEvents();
}
