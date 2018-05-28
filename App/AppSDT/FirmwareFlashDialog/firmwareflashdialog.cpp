#include "firmwareflashdialog.h"
#include "ui_firmwareflashdialog.h"
#include "FolderCompressor.h"
#include "sevdevice.h"
#include "gtutils.h"
#include "qttreemanager.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QProgressBar>
#include <QDebug>

#define FILENAME_XML_FLASHPRM "FlashPrm_AllAxis.xml"
#define FILENAME_XML_RAMPRM0 "PrmRAMAxis0.xml"
#define FILENAME_XML_RAMPRM1 "PrmRAMAxis1.xml"
#define FPGA_NAME "fpga"
#define DSP_NAME "dsp"
#define FILENAME_XML_FUNCEXTENSION "PrmFuncExtension.xml"

FirmwareFlashDialog::FirmwareFlashDialog(QList<SevDevice *> &devList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirmwareFlashDialog)
{
    ui->setupUi(this);
    uiInit();
    createConnections();
    m_devList = &devList;
    m_filePath = ".";
    m_desPath = "./DecompressdFiles";
    QDir dir(m_desPath);
    if (dir.exists()) {
        deleteDir(m_desPath);
    }
    dir.mkdir(m_desPath);
}

FirmwareFlashDialog::~FirmwareFlashDialog()
{
    delete ui;
}

void FirmwareFlashDialog::uiInit()
{
    ui->progressBar_firm->setVisible(false);
    ui->widget_firm->setVisible(false);
    for (int i = 0; i < m_devList->count(); i++) {
        ui->comboBox_firm->addItem(m_devList->at(i)->modelName());
    }
}

void FirmwareFlashDialog::createConnections()
{
    connect(ui->toolBtn_firm, SIGNAL(clicked()), this, SLOT(onActnToolbtnClicked()));
    connect(ui->btn_firmFlash, SIGNAL(clicked()), this, SLOT(onActnFlashBtnClicked()));
}

void FirmwareFlashDialog::processCallBack(void *argv, short *value)
{
    QProgressBar *pBar = static_cast<QProgressBar *>(argv);
    pBar->setValue(*value);
    qApp->processEvents();
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
    m_decompressPath = QFileDialog::getOpenFileName(0, tr("Open File"), m_filePath, tr("SDT Files(*.sdt)"));
    if (m_decompressPath.compare("") == 0) {
        return;
    }
    QFileInfo fileInfo;
    fileInfo.setFile(m_decompressPath);
    ui->lineEdit_firm->setText(fileInfo.fileName());
    m_filePath = m_decompressPath;
    ui->widget_firm->setVisible(true);
}

void FirmwareFlashDialog::onActnFlashBtnClicked()
{
    ui->infoDisplay_firm->clear();
    if (m_decompressPath.compare("") == 0) {
        return;
    }
    ui->progressBar_firm->setValue(0);
    ui->progressBar_firm->setVisible(true);
    ui->infoDisplay_firm->insertPlainText("Decompressing files!");
    FolderCompressor *folderComp = new FolderCompressor(0);
    bool ok = folderComp->decompressFolder(m_decompressPath, m_desPath);
    delete folderComp;
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText("Decompress fails!");
        deleteDir(m_desPath);
        ui->progressBar_firm->setVisible(false);
        return;
    }
    if (ui->checkBox_firmHex->isChecked()) {
        ok = downloadHexFile();
    }
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText("Downloading hex file fails!");
        deleteDir(m_desPath);
        ui->progressBar_firm->setVisible(false);
        return;
    }
    if (ui->checkBox_firmRpd->isChecked()) {
        ok = downloadRpdFile();
    }
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText("Downloading rpd file fails!");
        deleteDir(m_desPath);
        ui->progressBar_firm->setVisible(false);
        return;
    }
    if (ui->checkBox_firmXml->isChecked()) {
        ok = downloadXmlFiles();
    }
    if (!ok) {
        ui->infoDisplay_firm->insertPlainText("Downloading xml files fail!");
        deleteDir(m_desPath);
        ui->progressBar_firm->setVisible(false);
        return;
    }
    ui->infoDisplay_firm->insertPlainText("Downloading succeeds!");
    deleteDir(m_desPath);
    ui->progressBar_firm->setVisible(false);
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
    ui->infoDisplay_firm->insertPlainText("Downloading hex file");
    QStringList hexList = getFilesFromExt("hex", m_desPath, 1);
    QString hexPath = hexList.at(0);
    SevDevice* dev = m_devList->at(ui->comboBox_firm->currentIndex());
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
        qint16 ret = dev->socketCom()->downLoadDSPFLASH(i, hexPath.toStdWString(), processCallBack, (void *)ui->progressBar_firm);
        if (ret != 0) {
            return false;
        }
    }
    return true;
}

bool FirmwareFlashDialog::downloadRpdFile()
{
    SevDevice* dev = m_devList->at(ui->comboBox_firm->currentIndex());
    if (!dev->isConnecting()) {
        QMessageBox::information(0, tr("Warning"), tr("please open the com first !"));
        return false;
    }
    ui->infoDisplay_firm->insertPlainText("Downloading rpd file");
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
    SevDevice* dev = m_devList->at(ui->comboBox_firm->currentIndex());
    if (!dev->isConnecting()) {
        QMessageBox::information(0, tr("Warning"), tr("please open the com first !"));
        return false;
    }
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
