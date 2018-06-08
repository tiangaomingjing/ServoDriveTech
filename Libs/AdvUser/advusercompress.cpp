#include "advusercompress.h"
#include "ui_advusercompress.h"
#include "iadvuser_p.h"
#include "FolderCompressor.h"
#include "qttreemanager.h"
#include "dbmanager.h"
#include "gtutils.h"
#include "sdtglobaldef.h"

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
    ui->lineEdit_advFolderPath->clear();
    ui->lineEdit_advRpdVersion->clear();
    ui->lineEdit_advHexNote->clear();
    ui->lineEdit_advRpdNote->clear();
    ui->treeWidget->clear();
    setModify(false);
    QString treePath = GTUtils::sysPath() + "SysMap/ConfigSelectTree.ui";
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(treePath);
    QTreeWidgetItem *baseItem = tree->topLevelItem(1)->clone();
    delete tree;
    ui->treeWidget->addTopLevelItem(baseItem);
    ui->treeWidget->expandAll();
}

QString AdvUserCompress::nickName()
{
    return tr("Compress");
}

bool AdvUserCompress::advUserActive()
{
    Q_D(AdvUserCompress);
    QString hexNote = ui->lineEdit_advHexNote->text();
    QString rpdVersion = ui->lineEdit_advRpdVersion->text();
    QString rpdNote = ui->lineEdit_advRpdNote->text();
    QString hexVersion;
    if (ui->treeWidget->currentItem() == NULL || ui->treeWidget->currentItem()->childCount() != 0) {
        hexVersion = "";
    } else {
        hexVersion = ui->treeWidget->currentItem()->text(GT::COL_CONFIG_NAME).remove(0, 1);
    }
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
    QTreeWidgetItem *currentItem = ui->treeWidget->currentItem();
    QString xmlbasePath = currentItem->text(GT::COL_CONFIG_NAME);
    int count = 0;
    while (count < 2) {
        currentItem = currentItem->parent();
        xmlbasePath = currentItem->text(GT::COL_CONFIG_NAME) + "/" + xmlbasePath;
        count++;
    }
    QString xmlPath = GTUtils::sysPath() + xmlbasePath + "/" + FILENAME_XML_FLASHPRM;
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    if (tree != NULL) {
        QtTreeManager::writeTreeWidgetToXmlFile(d->m_compressPath + "/" + FILENAME_XML_FLASHPRM, tree);
        delete tree;
    }
    xmlPath = GTUtils::sysPath() + xmlbasePath + "/page/" + FILENAME_XML_RAMPRM0;
    tree = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    if (tree != NULL) {
        QtTreeManager::writeTreeWidgetToXmlFile(d->m_compressPath + "/" + FILENAME_XML_RAMPRM0, tree);
        delete tree;
    }
    xmlPath = GTUtils::sysPath() + xmlbasePath + "/page/" + FILENAME_XML_RAMPRM1;
    tree = QtTreeManager::createTreeWidgetFromXmlFile(xmlPath);
    if (tree != NULL) {
        QtTreeManager::writeTreeWidgetToXmlFile(d->m_compressPath + "/" + FILENAME_XML_RAMPRM1, tree);
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
    QString hexNoteStr = "HexNote:" + hexNote;
    QString rpdNoteStr = "RpdNode:" + rpdNote;
    in<<hexStr<<"\n"<<hexNoteStr<<"\n"<<rpdStr<<"\n"<<rpdNoteStr;
    file.close();
    FolderCompressor *folderComp = new FolderCompressor(0);
    QString dateStr = QDate::currentDate().toString("yyyyMMdd");
    QString modelName = ui->treeWidget->currentItem()->parent()->text(GT::COL_CONFIG_NAME);
    QString desFileName = modelName + "-V" + hexVersion + "-F" + rpdVersion + "-" + dateStr + ".sdt";
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
    infoDir.remove(FILENAME_XML_FLASHPRM);
    infoDir.remove(FILENAME_XML_RAMPRM0);
    infoDir.remove(FILENAME_XML_RAMPRM1);
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
