#include "firmwareflashdialog.h"
#include "ui_firmwareflashdialog.h"
#include "FolderCompressor.h"
#include "sevdevice.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include "dbmanager.h"
#include "deviceidhelper.h"
#include "optpath.h"
#include "optcontainer.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QProgressBar>
#include <QTextStream>
#include <QDebug>

#define FILENAME_XML_FLASHPRM "FlashPrm_AllAxis.xml"
#define FILENAME_XML_RAMPRM0 "PrmRAMAxis0.xml"
#define FILENAME_XML_RAMPRM1 "PrmRAMAxis1.xml"
#define FPGA_NAME "fpga"
#define DSP_NAME "dsp"
#define FILENAME_XML_FUNCEXTENSION "PrmFirmwareUpdate.xml"

FirmwareFlashDialog::FirmwareFlashDialog(QList<SevDevice *> &devList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirmwareFlashDialog)
{
    ui->setupUi(this);
    m_devList = devList;
    uiInit();
    m_filePath = ".";
    OptPath *optpath = dynamic_cast<OptPath *>(OptContainer::instance()->optItem("optpath"));
    if (optpath != NULL) {
        m_filePath = optpath->flashFilePath();
    }
    m_desPath = m_filePath + "/DecompressdFiles";
//    QDir dir(m_desPath);
//    if (dir.exists()) {
//        deleteDir(m_desPath);
//    }
//    dir.mkdir(m_desPath);
    createConnections();
}

FirmwareFlashDialog::~FirmwareFlashDialog()
{
    delete ui;
}

void FirmwareFlashDialog::uiInit()
{
    ui->progressBar_firm->setVisible(false);
    ui->widget_firm->setVisible(false);
    for (int i = 0; i < m_devList.length(); i++) {
        ui->comboBox_firm->addItem(m_devList.at(i)->modelName());
    }
    ui->comboBox_firm->setCurrentIndex(0);
}

void FirmwareFlashDialog::createConnections()
{
    connect(ui->toolBtn_firm, SIGNAL(clicked()), this, SLOT(onActnToolbtnClicked()));
    connect(ui->btn_firmFlash, SIGNAL(clicked()), this, SLOT(onActnFlashBtnClicked()));
    connect(ui->comboBox_firm, SIGNAL(currentIndexChanged(int)), this, SLOT(onActnComboBoxIndexChanged(int)));
}

void FirmwareFlashDialog::processCallBack(void *argv, short *value)
{
    QProgressBar *pBar = static_cast<QProgressBar *>(argv);
    pBar->setValue(*value);
    qApp->processEvents();
}

void FirmwareFlashDialog::closeEvent(QCloseEvent *event)
{
    QDir dir(m_desPath);
    if (dir.exists()) {
        deleteDir(m_desPath);
    }
    event->accept();
}

QStringList FirmwareFlashDialog::getFilesFromExt(const QString &fileExt, const QString &filePath, int num)
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

QString FirmwareFlashDialog::getFileFromName(const QString &fileName, const QString &filePath)
{
    QDir dir(filePath);
    if (!dir.exists()){
        return "";
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    for (int i = 0; i < fileList.count(); i++) {
        QFileInfo file = fileList.at(i);
        QString name = file.fileName();
        if (name.compare(fileName) == 0) {
            return name;
        }
    }
    return "";
}

void FirmwareFlashDialog::onActnToolbtnClicked()
{
    ui->lineEdit_firm->clear();
    ui->infoDisplay_firm->clear();
    m_decompressPath = QFileDialog::getOpenFileName(0, tr("Open File"), m_filePath, tr("SDT Files(*.sdt)"));
    if (m_decompressPath.compare("") == 0) {
        return;
    }
    QDir dir(m_desPath);
    if (dir.exists()) {
        deleteDir(m_desPath);
    }
    dir.mkdir(m_desPath);
    FolderCompressor *folderComp = new FolderCompressor(0);
    bool ok = folderComp->decompressFolder(m_decompressPath, m_desPath);
    delete folderComp;
    if (!ok) {
        QMessageBox::warning(this, tr("Warning"), tr("Decompressing fails!"));
        deleteDir(m_desPath);
        return;
    }
    QFileInfo fileInfo;
    fileInfo.setFile(m_decompressPath);
    ui->lineEdit_firm->setText(fileInfo.fileName());
    m_filePath = m_decompressPath;
    ui->widget_firm->setVisible(true);

    QFile infoFile(m_desPath + "/infoFile.ini");
    if (!infoFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("File open fails!"));
        deleteDir(m_desPath);
        return;
    }
    QTextStream in(&infoFile);
    QString line = in.readLine();
    QStringList lineList = line.split(":");
    m_dspVersion = lineList.last();
    ui->infoDisplay_firm->insertPlainText("DSP Version: " + m_dspVersion + "\n");

    line = in.readLine();
    lineList = line.split(":");
    QString hexNote = lineList.last();
    ui->infoDisplay_firm->insertPlainText("DSP Note: " + hexNote + "\n");


    line = in.readLine();
    lineList = line.split(":");
    m_fpgVersion = lineList.last();
    ui->infoDisplay_firm->insertPlainText("FPGA Version: " + m_fpgVersion + "\n");

    line = in.readLine();
    lineList = line.split(":");
    QString fpgaNote = lineList.last();
    ui->infoDisplay_firm->insertPlainText("FPGA Note: " + fpgaNote + "\n");

    onActnComboBoxIndexChanged(ui->comboBox_firm->currentIndex());
}

void FirmwareFlashDialog::onActnFlashBtnClicked()
{
    if (m_decompressPath.compare("") == 0) {
        return;
    }
    ui->progressBar_firm->setValue(0);
    ui->progressBar_firm->setVisible(true);
    ui->infoDisplay_firm->insertPlainText(tr("1.Checking version!\n"));

    SevDevice *dev = m_devList.at(ui->comboBox_firm->currentIndex());
    DeviceIdHelper *idHelper = new DeviceIdHelper(dev->socketCom(), 0);
    bool ok = true;
    int servoIndex = -1;
    for (int i = 0; i < dev->axisNum(); i++) {
        if (dev->axisServoIsOn(i)) {
            ok = false;
            servoIndex = i;
            break;
        }
    }
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText(tr("Axis%1 is on servo!").arg(servoIndex));
        delete idHelper;
        return;
    }
    quint32 pwrId = idHelper->readPwrId(ok);
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText(tr("Reading powerboard Id fails!\n"));
        delete idHelper;
        return;
    }
    QString pwrStr = QString::number(pwrId);

    quint32 ctrId = idHelper->readCtrId(ok);
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText(tr("Reading controlboard Id fails!\n"));
        delete idHelper;
        return;
    }
    QString ctrStr = QString::number(ctrId);
    delete idHelper;

    DBManager *dbManager = new DBManager(GTUtils::databasePath() + "Version/", "root", "");
    QStringList verList;
    verList<<ctrStr<<m_dspVersion<<m_fpgVersion<<pwrStr;
    ok = dbManager->checkValid(verList);
    delete dbManager;
    if (!ok) {
        QMessageBox::StandardButton rb = QMessageBox::question(0, tr("Warning"), tr("Version do not match. Are you sure to continue?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (!(rb == QMessageBox::Yes)) {
            return;
        }
    }
    ok = true;
    if (ui->checkBox_firmHex->isChecked()) {
        ok = downloadHexFile();
    }
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText(tr("Downloading hex file fails!\n"));
        deleteDir(m_desPath);
        ui->progressBar_firm->setVisible(false);
        return;
    }
    if (ui->checkBox_firmXml->isChecked()) {
        ok = downloadXmlFiles();
    }
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText(tr("Downloading xml files fail!\n"));
        deleteDir(m_desPath);
        ui->progressBar_firm->setVisible(false);
        return;
    }
    if (ui->checkBox_firmRpd->isChecked()) {
        ok = downloadRpdFile();
    }
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText(tr("Downloading rpd file fails!\n"));
        deleteDir(m_desPath);
        ui->progressBar_firm->setVisible(false);
        return;
    }
    ui->infoDisplay_firm->insertPlainText(tr("Downloading succeeds!\n"));
    deleteDir(m_desPath);
    ui->progressBar_firm->setVisible(false);
}

void FirmwareFlashDialog::onActnComboBoxIndexChanged(int index)
{
    quint16 year = 0;
    quint16 day = 0;
    DeviceIdHelper *idHelper = new DeviceIdHelper(m_devList.at(index)->socketCom(), 0);
    bool ok = idHelper->readFpgaDate(year, day);
    delete idHelper;
    if (!ok) {
        qDebug()<<"read err";
        return;
    }
    QString fpgDate = QString("%1%2").arg(QString::asprintf("%04X", year)).arg(QString::asprintf("%04X", day));
    qDebug()<<"fpgdate"<<fpgDate;
    if (fpgDate.compare(m_fpgVersion) == 0) {
        ui->checkBox_firmRpd->setChecked(false);
    } else {
        ui->checkBox_firmRpd->setChecked(true);
    }
}

bool FirmwareFlashDialog::deleteDir(const QString &path)
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

bool FirmwareFlashDialog::downloadHexFile()
{
    ui->infoDisplay_firm->insertPlainText(tr("2.Downloading hex file!\n"));
    QStringList hexList = getFilesFromExt("hex", m_desPath, 1);
    QString hexPath = hexList.at(0);
    SevDevice* dev = m_devList.at(ui->comboBox_firm->currentIndex());
    if (!dev->isConnecting()) {
        QMessageBox::information(0, tr("Warning"), tr("please open the com first !"));
        return false;
    }
    int dspNum;
    QString filePath = GTUtils::sysPath() + dev->typeName() + "/" + dev->modelName() + "/" \
                       + dev->versionName() + "/" + FILENAME_XML_FUNCEXTENSION;
    QTreeWidget* tree = QtTreeManager::createTreeWidgetFromXmlFile(filePath);
    QTreeWidgetItem *dspItem = GTUtils::findItem(DSP_NAME, tree, GT::COL_PRMEXT_NAME);
    if (dspItem != NULL) {
        dspNum = dspItem->text(GT::COL_PRMEXT_PARA).toInt();
    } else {
        dspNum = (dev->axisNum() + 1) / 2;
    }
    delete tree;
    for (int i = 0; i < dspNum; i++) {
        ui->infoDisplay_firm->insertPlainText(tr("Downloading DSP %1.\n").arg(i + 1));
        qint16 ret = dev->socketCom()->downLoadDSPFLASH(i, hexPath.toStdWString(), processCallBack, (void *)ui->progressBar_firm);        
        if (ret != 0) {
            return false;
        }
    }
    return true;
}

bool FirmwareFlashDialog::downloadRpdFile()
{
    SevDevice* dev = m_devList.at(ui->comboBox_firm->currentIndex());
    if (!dev->isConnecting()) {
        QMessageBox::information(0, tr("Warning"), tr("please open the com first !"));
        return false;
    }
    ui->infoDisplay_firm->insertPlainText(tr("4.Downloading rpd file!\n"));
    QStringList rpdList = getFilesFromExt("rpd", m_desPath, 1);
    QString rpdPath = rpdList.at(0);
    int fpgNum;
    int fpgAxis;
    QString filePath = GTUtils::sysPath() + dev->typeName() + "/" + dev->modelName() + "/" \
                       + dev->versionName() + "/" + FILENAME_XML_FUNCEXTENSION;
    QTreeWidget* tree = QtTreeManager::createTreeWidgetFromXmlFile(filePath);
    QTreeWidgetItem *fpgItem = GTUtils::findItem(FPGA_NAME, tree, GT::COL_PRMEXT_NAME);
    if (fpgItem != NULL) {
        fpgNum = fpgItem->text(GT::COL_PRMEXT_PARA).toInt();
        fpgAxis= fpgItem->child(0)->text(GT::COL_PRMEXT_PARA).toInt();
    } else {
        fpgNum = 1;
        fpgAxis = dev->axisNum();
    }
    delete tree;
    for (int i = 0; i < fpgNum; i++) {
        qint16 ret = dev->socketCom()->downLoadFPGAFLASH(i * fpgAxis, rpdPath.toStdWString(), processCallBack, (void *)ui->progressBar_firm);
        if (ret != 0) {
            return false;
        }
    }
    return true;
}

bool FirmwareFlashDialog::downloadXmlFiles()
{
    SevDevice* dev = m_devList.at(ui->comboBox_firm->currentIndex());
    if (!dev->isConnecting()) {
        QMessageBox::information(0, tr("Warning"), tr("please open the com first !"));
        return false;
    }
    ui->infoDisplay_firm->insertPlainText(tr("3.Downloading xml files!\n"));
    QStringList fileNameList;
    fileNameList.append(m_desPath + "/" + FILENAME_XML_FLASHPRM);
    fileNameList.append(m_desPath + "/" + FILENAME_XML_RAMPRM0);
    fileNameList.append(m_desPath + "/" + FILENAME_XML_RAMPRM1);
    QList<int> fileTypeList;
    fileTypeList<<0<<0<<0;
    quint8 axis = 0;
    short value = ui->progressBar_firm->value();
    bool ok = dev->writeXml(axis, fileNameList, fileTypeList, fileNameList.length(), processCallBack, ui->progressBar_firm, value);
    return ok;
}
