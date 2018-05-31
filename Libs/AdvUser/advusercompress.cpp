#include "advusercompress.h"
#include "ui_advusercompress.h"
#include "iadvuser_p.h"
#include "FolderCompressor.h"
#include "qttreemanager.h"
#include "dbmanager.h"
#include "gtutils.h"

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QMessageBox>
#include <QTreeWidget>
#include <QDebug>

#define FILENAME_XML_FLASHPRM "FlashPrm_AllAxis.xml"
#define FILENAME_XML_RAMPRM0 "PrmRAMAxis0.xml"
#define FILENAME_XML_RAMPRM1 "PrmRAMAxis1.xml"

class AdvUserCompressPrivate : public IAdvUserPrivate {
    Q_DECLARE_PUBLIC(AdvUserCompress)
public:
    AdvUserCompressPrivate();
    ~AdvUserCompressPrivate();
    QString m_filePath;
    QString m_compressPath;
};

AdvUserCompressPrivate::AdvUserCompressPrivate()
{
    m_compressPath = "";
}

AdvUserCompressPrivate::~AdvUserCompressPrivate()
{

}

AdvUserCompress::AdvUserCompress(const QString &advUserName, QWidget *parent) :
    IAdvUser(advUserName, *new AdvUserCompressPrivate, parent),
    ui(new Ui::AdvUserCompress)
{
    ui->setupUi(this);
    readAdv();
    uiInit();
    connect(ui->toolBtn_advCompress, SIGNAL(clicked()), this, SLOT(onActnCompressToolBtnClicked()));
}

AdvUserCompress::~AdvUserCompress()
{
    delete ui;
}

void AdvUserCompress::uiInit()
{

}

bool AdvUserCompress::advUserActive()
{
    Q_D(AdvUserCompress);
    QString hexVersion = ui->lineEdit_advHexVersion->text();
    QString rpdVersion = ui->lineEdit_advRpdVersion->text();
    if (hexVersion.compare("") == 0 || rpdVersion.compare("") == 0) {
        QMessageBox::information(0, tr("Compress"), tr("Please enter version information"));
        return false;
    }
    DBManager *dbManager = new DBManager(GTUtils::databasePath() + "Version/", "root", "");
    bool ok = dbManager->checkCoupleValid(hexVersion, rpdVersion, 1, 2);
    delete dbManager;
    if (!ok) {
        QMessageBox::StandardButton rb = QMessageBox::question(0, tr("Compress"), tr("Version do not match. Are you sure to continue?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (!(rb == QMessageBox::Yes)) {
            return false;
        }
    }
    QString xmlPath = d->m_compressPath + "/" + FILENAME_XML_FLASHPRM;
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    if (tree != NULL) {
        QtTreeManager::writeTreeWidgetToXmlFile(xmlPath, tree);
        delete tree;
    }
    xmlPath = d->m_compressPath + "/" + FILENAME_XML_RAMPRM0;
    tree = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    if (tree != NULL) {
        QtTreeManager::writeTreeWidgetToXmlFile(xmlPath, tree);
        delete tree;
    }
    xmlPath = d->m_compressPath + "/" + FILENAME_XML_RAMPRM1;
    tree = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    if (tree != NULL) {
        QtTreeManager::writeTreeWidgetToXmlFile(xmlPath, tree);
        delete tree;
    }
    QString infoFilePath = d->m_compressPath + "/infoFile.ini";
    QFile file(infoFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    QString hexStr = "Hex:" + hexVersion;
    QString rpdStr = "Rpd:" + rpdVersion;
    in<<hexStr<<"\n"<<rpdStr;
    file.close();
    FolderCompressor *folderComp = new FolderCompressor(0);
    QString dateStr = QString::number(QDate::currentDate().year()) + QString::number(QDate::currentDate().month()) + QString::number(QDate::currentDate().day());
    QString desFileName = "V" + hexVersion + "-" + "F" + rpdVersion + "-" + dateStr + ".sdt";
    QDir compDir(d->m_compressPath);
    compDir.cdUp();
    QString desStr = compDir.absolutePath() + "/" + desFileName;
    ok = folderComp->compressFolder(d->m_compressPath, desStr);
    if (!ok) {
        QMessageBox::information(0, tr("Compress"), tr("Compressing fails!"));
        delete folderComp;
        return false;
    }
    delete folderComp;
    QDir infoDir(d->m_compressPath);
    infoDir.remove("infoFile.ini");
    return true;
}

bool AdvUserCompress::readAdv()
{
    Q_D(AdvUserCompress);
    d->m_filePath = dataFromFile("advCompress", "filePath", ".").toString();
    QDir dir(d->m_filePath);
    if (dir.exists()) {
        d->m_filePath = ".";
    }
    return true;
}

bool AdvUserCompress::writeAdv()
{
    Q_D(AdvUserCompress);
    saveDataToFile("advCompress", "filePath", d->m_filePath);
    return true;
}

void AdvUserCompress::respondErrorExecute()
{

}

void AdvUserCompress::onActnCompressToolBtnClicked()
{
    Q_D(AdvUserCompress);
    ui->lineEdit_advFolderPath->clear();
    d->m_compressPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), d->m_filePath);
    if (d->m_compressPath.compare("") == 0) {
        return;
    }
    ui->lineEdit_advFolderPath->setText(d->m_compressPath);
    QDir compDir(d->m_compressPath);
    compDir.cdUp();
    d->m_filePath = compDir.absolutePath();
    setModify(true);
}
