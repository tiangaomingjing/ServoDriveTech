#include "flashclass.h"
#include "jsonreader.h"
#include "ServoDriverComDll.h"
#include "treemanager.h"
#include "controlservo.h"
#include "globaldefine.h"
#include "gtutils.h"
#include <QProgressBar>

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

void FlashClass::flash(int netId, QString hexPath, QString xmlPath, int dspNum, QObject *proBar) {
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
    QString filePath = GTUtils::databasePath() + "Board/NetConfig.json";
    net.initialDataFromJsonFile(filePath);
    qint16 netRnStation = net.rnStation();
    m_netRnStation = netRnStation;
    QString outPath = GTUtils::databasePath() + "Board/ServoUboot.out";
    QString ldrPath = GTUtils::databasePath() + "Board/ServoUboot.ldr";
    emit sendWarnMsg(tr("Servo ubooting......"));
    if(0 == GTSD_CMD_Hex2Ldr(outPath.toStdWString(), ldrPath.toStdWString(), netId, netRnStation))//转化文件成功
    {

        bool ubootOk = uBoot(ldrPath, net, proBar);
        if (ubootOk)
        {
            bool isHexDownload = downloadHex(proBar);
            emit sendWarnMsg(tr("Download hex-file to servo complete!"));
            delayms(20);
            if (isHexDownload)//hex文件下载成功
            {
                ControlServo scontrol;
                connect(&scontrol,SIGNAL(progressValue(int)),this,SLOT(onXmlPrmToServo(int)));
                emit sendWarnMsg(tr("Download xml parameters file to servo......"));
                delayms(20);
                emit changeBarCount(20);
                delayms(20);            
                scontrol.writeServoFlashByAllAxisTree(treePrm,(COM_TYPE)netId,netRnStation);
                qDebug()<<"write file to servo complete";
                emit changeBarCount(60);
                delayms(20);
                emit changeBarCount(70);
                treePrm->clear();
                delete treePrm;
                emit sendWarnMsg(tr("Download xml parameters file to servo complete successfully!"));
                emit changeBarCount(80);
                delayms(20);
                emit changeBarCount(100);
                emit sendWarnMsg(tr("Flash successfully!"));
                delayms(20);

                m_progessValue = 0;
                m_step = 0;
                        //ui->progressBar->setVisible(false);
                emit changeBarCount(0);
            }
            else
            {
                emit sendWarnMsg(tr("Download hex file error!"));
            }
        }
        else
        {
            emit sendWarnMsg(tr("Uboot .out file error! Maybe you are not in the uboot or hardwares have some problems."));
        }
        emit changeBarCount(0);
                //ui->progressBar->hide();
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

bool FlashClass::downloadHex(QObject *proBar) {
    bool isHexDownload = false;
    int result = 0;
    for (int i = 0; i < m_dspNum; i++)
    {
        m_step = i;
        int axisNum = i + 1;
        emit sendWarnMsg(tr("Flashing DSP ") + QString("%1").arg(axisNum) + "!");
        result = GTSD_CMD_ProcessorFlashHandler(i * 2, m_hexPath.toStdWString(),updateProgessBarWhenRestoreClicked,(void*)proBar, m_netId, m_netRnStation);
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
