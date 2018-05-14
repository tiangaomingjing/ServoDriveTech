#include "eprommanager.h"
#include "ui_eprommanager.h"
#include "treemanager.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QCloseEvent>
#include <QDataStream>
#include "flashclass.h"
#include "tcpconnect.h"
#include "gtutils.h"



EpromManager::EpromManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EpromManager)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    m_tcpClient = new TcpConnect();
    connect(m_tcpClient, SIGNAL(receiveConfig(QStringList)), this, SLOT(receiveConfig(QStringList)));
    m_tcpClient->connectToServer();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    QString str = "Start";
    out<<quint16(0)<<str;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpClient->sendRequest(block);
    qDebug()<<"str"<<str;

    m_tcpClient->waitforMs(1000);
    m_tcpClient->stopConnection();
    initializeTree();

    m_filePath = ".";
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    ui->list->item(0)->setIcon(QIcon(GTUtils::iconPath() + "Select.png"));
    ui->list->item(1)->setIcon(QIcon(GTUtils::iconPath() + "menu_restoresetting.png"));
    ui->list->item(2)->setIcon(QIcon(GTUtils::iconPath() + "Power.png"));
    ui->list->item(3)->setIcon(QIcon(GTUtils::iconPath() + "Control.png"));
    connect(ui->list, SIGNAL(currentRowChanged(int)), ui->stack, SLOT(setCurrentIndex(int)));
    setComConnectStatus(false);

    ui->hexLine->setReadOnly(true);
    ui->xmlLine->setReadOnly(true);
    ui->flashButton->setEnabled(false);
    ui->writeButton->setEnabled(false);
    ui->readButton->setEnabled(false);
    ui->compareButton->setEnabled(false);
    ui->writeButton_2->setEnabled(false);
    ui->readButton_2->setEnabled(false);
    ui->compareButton_2->setEnabled(false);
    ui->hexButton->setEnabled(false);
    ui->xmlButton->setEnabled(false);
    QRegExp regExp("^[0-9]{1,9}|[0-3][0-9]{9}|4[0-1][0-9]{8}|42[0-8][0-9]{7}|429[0-3][0-9]{6}|4294[0-8][0-9]{5}|42949[0-5][0-9]{4}|429496[0-6][0-9]{3}|4294967[0-1][0-9]{2}|42949672[0-8][0-9]|429496729[0-5]$");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp, this));
    ui->lineEdit_2->setValidator(new QRegExpValidator(regExp, this));

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(onLineTextChange(QString)));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(onLineTextChange_2(QString)));

    connect(ui->selectTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeItemClicked(QTreeWidgetItem*,int)));

    connect(ui->writeButton, SIGNAL(clicked()), this, SLOT(onWriteClicked()));
    connect(ui->writeButton_2, SIGNAL(clicked()), this, SLOT(onWriteClicked_2()));

    connect(ui->readButton, SIGNAL(clicked()), this, SLOT(onReadClicked()));
    connect(ui->readButton_2, SIGNAL(clicked()), this, SLOT(onReadClicked_2()));

    connect(ui->compareButton, SIGNAL(clicked()), this, SLOT(onCompareClicked()));
    connect(ui->compareButton_2, SIGNAL(clicked()), this, SLOT(onCompareClicked_2()));

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onActionConnectClicked()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(onActionDisConnectClicked()));

    connect(ui->hexButton, SIGNAL(clicked()), this, SLOT(selectHex()));
    connect(ui->xmlButton, SIGNAL(clicked()), this, SLOT(selectXml()));
    connect(ui->flashButton, SIGNAL(clicked()), this, SLOT(onActionFlashClicked()));
}

EpromManager::~EpromManager()
{
    delete ui;
}

void EpromManager::initializeTree() {
    showSelectTree();
    ui->selectTree->topLevelItem(0)->child(0)->setSelected(true);
    m_powerIndex = TreeManager::createTreeWidgetFromXmlFile(GTUtils::databasePath() + "Board/PB/pbindex.ui");
    m_controlIndex = TreeManager::createTreeWidgetFromXmlFile(GTUtils::databasePath() + "Board/CB/cbindex.ui");
    m_powerMap = TreeManager::createTreeWidgetFromXmlFile(GTUtils::databasePath() + "Board/PB/IdMap_Power.ui");
    m_controlMap = TreeManager::createTreeWidgetFromXmlFile(GTUtils::databasePath() + "Board/CB/IdMap_Control.ui");
    treeItemClicked(ui->selectTree->topLevelItem(0)->child(0), 0);
}

com_type EpromManager::getComType() {
    if (m_comText.compare("PcDebug") == 0) {
        return GTSD_COM_TYPE_NET;
    } else {
        return GTSD_COM_TYPE_RNNET;
    }
}

void EpromManager::onBarUpdate() {
    m_barCount++;
    if (m_barCount % 10 == 0) {
        ui->progressBar->setValue(m_barCount % 100);
    }
}

void EpromManager::showWarn(QString msg) {
    ui->warnLabel->setText(msg);
}

void EpromManager::setBarCount(int value) {
    m_barCount = value;
    if (m_barCount % 10 == 0) {
        ui->progressBar->setValue(m_barCount % 100);
    }
}

/************ show the tree in the select part & write tab ******************/
void EpromManager::onOkClicked() {
    ui->writeButton->setEnabled(true);
    ui->readButton->setEnabled(true);
    ui->writeButton_2->setEnabled(true);
    ui->readButton_2->setEnabled(true);
    ui->hexButton->setEnabled(true);
    ui->xmlButton->setEnabled(true);
    showTree(m_powerID, m_powerBoard->getTree(), ui->treeWidget);
    showTree(m_controlID, m_controlBoard->getTree(), ui->treeWidget_2);
}

void EpromManager::showSelectTree() {
    if (m_typeName.compare("") != 0 && m_modeName.compare("") != 0) {
        QTreeWidgetItem *typeItem = new QTreeWidgetItem;
        typeItem->setText(0, m_typeName);
        QTreeWidgetItem *modeItem = new QTreeWidgetItem;
        modeItem->setText(0, m_modeName);
        typeItem->addChild(modeItem);
        ui->selectTree->addTopLevelItem(typeItem);
        ui->selectTree->expandAll();
        ui->selectTree->resizeColumnToContents(0);
        m_tcpSuccess = true;
    } else {
        QTreeWidget *tree = TreeManager::createTreeWidgetFromXmlFile(GTUtils::databasePath() + "Board/SelectTree.ui");
        for (int i = 0; i < tree->topLevelItemCount(); i++) {
            ui->selectTree->addTopLevelItem(tree->topLevelItem(i)->clone());
        }
        ui->selectTree->expandAll();
        ui->selectTree->resizeColumnToContents(0);
        delete tree;
        m_tcpSuccess = false;
    }
}

/**************************************************************/

/********************** write *************************/
void EpromManager::onWriteClicked() {
    //QString typeText = ui->typeLabel->text();
    QString code = ui->lineEdit->text();
    if (code == "") {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter a PCBA code!"), QMessageBox::Ok);
        return;
    }
    int ret = QMessageBox::question(this, tr("Question"), tr("Are you sure to write\n") + m_itemText + "?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    ui->lineEdit->setReadOnly(true);
    ui->readButton->setEnabled(false);
    ui->warnLabel->clear();
    ui->progressBar->setRange(0, 100);
    ui->progressBar->show();
    m_barCount = 0;
    ui->progressBar->setValue(m_barCount);
    bool ok;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        ok = m_powerBoard->writeFromXmltoEprom(item);
        if (!ok) {
            break;
        }
    }
    ui->progressBar->hide();
    ui->lineEdit->setReadOnly(false);
    ui->readButton->setEnabled(true);

    ui->tabWidget->setCurrentIndex(1);
    if (ok) {
        onReadClicked();
    }
}

void EpromManager::onWriteClicked_2() {
    //QString typeText = ui->typeLabel->text();
    QString code = ui->lineEdit_2->text();
    if (code == "") {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter a PCBA code!"), QMessageBox::Ok);
        return;
    }
    int ret = QMessageBox::question(this, tr("Question"), tr("Are you sure to write\n") + m_itemText + "?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    ui->lineEdit_2->setReadOnly(true);
    ui->readButton_2->setEnabled(false);
    ui->warnLabel->clear();
    ui->progressBar->setRange(0, 100);
    ui->progressBar->show();
    m_barCount = 0;
    ui->progressBar->setValue(m_barCount);
    bool ok;
    for (int i = 0; i < ui->treeWidget_2->topLevelItemCount(); i++) {
        QTreeWidgetItem *item = ui->treeWidget_2->topLevelItem(i);
        ok = m_controlBoard->writeFromXmltoEprom(item);
        if (!ok) {
            break;
        }
    }
    ui->progressBar->hide();
    ui->lineEdit_2->setReadOnly(false);
    ui->readButton_2->setEnabled(true);

    ui->tabWidget_2->setCurrentIndex(1);
    if (ok) {
        onReadClicked_2();
    }
}

void EpromManager::treeItemClicked(QTreeWidgetItem* item, int column) {
    m_itemText = item->text(column);
    //qDebug()<<"item text"<<m_itemText;
    if (item->childCount() == 0) {
        m_modeName = m_itemText;
        m_typeName = item->parent()->text(column);
        QTreeWidgetItem *controlItem = GLO::findItem(m_itemText, m_controlMap, IDMAP_MODE);
        QTreeWidgetItem *powerItem = GLO::findItem(m_itemText, m_powerMap, IDMAP_MODE);
        m_powerID = powerItem->text(IDMAP_ID);
        m_controlID = controlItem->text(IDMAP_ID);
        if (!m_tcpSuccess) {
            m_dspNum = item->text(column + 1).toInt();
        }
        QTreeWidgetItem *powerIndexItem = GLO::findItem(m_powerID, m_powerIndex, TREE_VALUE);
        QTreeWidgetItem *controlIndexItem = GLO::findItem(m_controlID, m_controlIndex, TREE_VALUE);
        m_powerPath = GLO::getPath(powerIndexItem) + "/" + m_powerID + "/" + m_powerID + ".ui";
        m_controlPath = GLO::getPath(controlIndexItem) + "/" + m_controlID + "/" + m_controlID + ".ui";
        m_powerPath = GTUtils::databasePath() + "Board/PB/" + m_powerPath;
        m_controlPath = GTUtils::databasePath() + "Board/CB/" + m_controlPath;
        changeConfigText(m_powerID, m_powerIndex);
    }
    showText(m_configText, m_comText);
}

void EpromManager::changeConfigText(QString text, QTreeWidget *tree) {
    QTreeWidgetItem *item = GLO::findItem(text, tree, TREE_VALUE);
    m_configText = item->text(TREE_NAME);
    int count = 0;
    QTreeWidgetItem *currentItem = item;
    while (count < 3) {
        currentItem = currentItem->parent();
        m_configText = currentItem->text(TREE_NAME) + "->\n" + m_configText;
        count++;
    }
}

void EpromManager::showText(QString configText, QString comText) {
    QString typeText = configText + "\n\n" + "Com Type:\n" + comText;
    ui->typeLabel->setText(typeText);
}


void EpromManager::showTree(QString text, QTreeWidget *tree, QTreeWidget *uiTree) {
    QTreeWidgetItem *item = GLO::findItem(text, tree, TREE_VALUE);
    uiTree->clear();
    for (int i = 0; i < tree->topLevelItemCount(); i++) {
        uiTree->addTopLevelItem(tree->topLevelItem(i)->clone());
    }
    uiTree->expandAll();
    uiTree->resizeColumnToContents(0);
    delete item;
}

/*******************************************************************************/

/*************************** read **********************************************/

void EpromManager::onReadClicked() {
    ui->readTreeWidget->clear();
    ui->warnLabel->clear();
    ui->progressBar->show();
    m_barCount = 0;
    ui->progressBar->setValue(0);
    bool ok = m_powerBoard->readFromEprom(ui->readTreeWidget);
    if (ok && ui->readTreeWidget->topLevelItemCount() != 0) {
        onCompareClicked();
    }
    ui->progressBar->hide();
    ui->compareButton->setEnabled(true);
}

void EpromManager::onReadClicked_2() {
    ui->readTreeWidget_2->clear();
    ui->warnLabel->clear();
    ui->progressBar->show();
    m_barCount = 0;
    ui->progressBar->setValue(m_barCount);
    bool ok = m_controlBoard->readFromEprom(ui->readTreeWidget_2);
    if (ok && ui->readTreeWidget_2->topLevelItemCount() != 0) {
        onCompareClicked_2();
    }
    ui->progressBar->hide();
    ui->compareButton_2->setEnabled(true);
}

/*******************************************************************************/

/**************************** compare ******************************************/
void EpromManager::onCompareClicked() {
    ui->warnLabel->clear();
    ui->progressBar->show();
    m_barCount = 0;
    ui->progressBar->setValue(m_barCount);
    m_powerBoard->compare(ui->readTreeWidget);
    ui->progressBar->hide();
}

void EpromManager::onCompareClicked_2() {
    ui->warnLabel->clear();
    ui->progressBar->show();
    m_barCount = 0;
    ui->progressBar->setValue(m_barCount);
    m_controlBoard->compare(ui->readTreeWidget_2);
    ui->progressBar->hide();
}

/******************************************************************************/

/***************************** open & close ***********************************/
void EpromManager::onActionConnectClicked() {
        COM_ERROR error = COM_OK;
        ui->progressBar->show();
        error = static_cast<COM_ERROR>(GTSD_CMD_Open(updateProgessBar, (void*)ui->progressBar, getComType()));
        if (error != COM_OK) {
            GTSD_CMD_Close(getComType());
            ui->connectIcon->setIcon(QIcon(GTUtils::iconPath() + ICON_STATUS_DISCONNECT));
            m_isOpenCom = false;
            QMessageBox::warning(this, tr("Warning"), tr("Connection Failed!"), QMessageBox::Ok);
        } else {
            ui->connectButton->setEnabled(false);
            ui->connectIcon->setIcon(QIcon(GTUtils::iconPath() + ICON_STATUS_CONNECT));
            m_isOpenCom = true;
            com_type comType = getComType();
            m_powerBoard = new EPROM_POWER(m_powerPath, comType);
            m_controlBoard = new EPROM_CONTROL(m_controlPath, comType);
            connect(m_powerBoard, SIGNAL(updateBarCount()), this, SLOT(onBarUpdate()));
            connect(m_powerBoard, SIGNAL(sendWarnMsg(QString)), this, SLOT(showWarn(QString)));
            connect(m_powerBoard, SIGNAL(changeBarCount(int)), this, SLOT(setBarCount(int)));
            connect(m_powerBoard, SIGNAL(sendScrollItem(QTreeWidgetItem*)), this, SLOT(scrollTree(QTreeWidgetItem*)));
            connect(m_controlBoard, SIGNAL(updateBarCount()), this, SLOT(onBarUpdate()));
            connect(m_controlBoard, SIGNAL(sendWarnMsg(QString)), this, SLOT(showWarn(QString)));
            connect(m_controlBoard, SIGNAL(changeBarCount(int)), this, SLOT(setBarCount(int)));
            connect(m_controlBoard, SIGNAL(sendScrollItem(QTreeWidgetItem*)), this, SLOT(scrollTree_2(QTreeWidgetItem*)));
            onOkClicked();
        }
        ui->progressBar->hide();
}

void EpromManager::onActionDisConnectClicked() {
    if (m_isOpenCom) {
        GTSD_CMD_Close(getComType());
        ui->connectIcon->setIcon(QIcon(GTUtils::iconPath() + ICON_STATUS_DISCONNECT));
        m_isOpenCom = false;
        ui->connectButton->setEnabled(true);
        ui->writeButton->setEnabled(false);
        ui->readButton->setEnabled(false);
        ui->compareButton->setEnabled(false);
        ui->writeButton_2->setEnabled(false);
        ui->readButton_2->setEnabled(false);
        ui->compareButton_2->setEnabled(false);
        ui->flashButton->setEnabled(false);
        ui->warnLabel->clear();
        ui->hexLine->clear();
        ui->xmlLine->clear();
        ui->treeWidget->clear();
        ui->treeWidget_2->clear();
        delete m_powerBoard;
        delete m_controlBoard;
    }
}

void EpromManager::updateProgessBar(void *arg, qint16 *value)
{
    QProgressBar *bar = static_cast<QProgressBar *>(arg);
    bar->setValue(*value);
    qApp->processEvents();
    //qDebug()<<"value "<<*value;
}

void EpromManager::setComConnectStatus(bool isConnected)
{
    if(isConnected)
    {
        ui->connectIcon->setIcon(QIcon(GTUtils::iconPath() + ICON_STATUS_CONNECT));
        m_isOpenCom = true;
    }
    else
    {
        ui->connectIcon->setIcon(QIcon(GTUtils::iconPath() + ICON_STATUS_DISCONNECT));
        m_isOpenCom = false;
    }
}
/**************************************************************************/

/****************************** flash *************************************/
void EpromManager::selectHex() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open"), m_filePath, tr("Hex Files( *.hex)"));
    if(path.isNull())
        return;
    QFileInfo fileInfo;
    fileInfo.setFile(path);
    m_filePath = fileInfo.filePath() + "/";
    ui->hexLine->setText(fileInfo.fileName());
    m_hexPath = path;
    if (!m_hexPath.isNull() && !m_xmlPath.isNull()) {
        ui->flashButton->setEnabled(true);
    }
}

void EpromManager::selectXml() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open"), m_filePath, tr("Xml Files( *.xml)"));
    if(path.isNull())
      return;
    QFileInfo fileInfo;
    fileInfo.setFile(path);
    m_filePath = fileInfo.filePath()+"/";
    ui->xmlLine->setText(fileInfo.fileName());
    m_xmlPath = path;
    if (!m_hexPath.isNull() && !m_xmlPath.isNull()) {
        ui->flashButton->setEnabled(true);
    }
}

void EpromManager::onActionFlashClicked() {
    if (m_isOpenCom) {
        int ret = QMessageBox::question(this, tr("Question"), tr("Do you want to uboot?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (ret == QMessageBox::No) {
            return;
        }
        FlashClass *flashManager = new FlashClass();
        connect(flashManager, SIGNAL(sendWarnMsg(QString)), this, SLOT(showWarn(QString)));
        connect(flashManager, SIGNAL(changeBarCount(int)), this, SLOT(setBarCount(int)));
        ui->progressBar->setVisible(true);
        ui->warnLabel->setEnabled(true);
        ui->progressBar->setValue(2);
        flashManager->flash(getComType(), m_hexPath, m_xmlPath, m_dspNum, ui->progressBar);
        ui->progressBar->setVisible(false);
        delete flashManager;
    } else {
        QMessageBox::information(this, tr("Information"), tr("Please connect the device!"), QMessageBox::Ok);
    }
}
/*****************************************************************************/

void EpromManager::onLineTextChange(QString text) {
    onTextChange(text, ui->treeWidget, m_powerID);
}

void EpromManager::onLineTextChange_2(QString text) {
    onTextChange(text, ui->treeWidget_2, m_controlID);
}

void EpromManager::onTextChange(QString text, QTreeWidget *tree, const QString &id) {
    QTreeWidgetItem *item = GLO::findItem("PCBA code", tree, TREE_NAME);
    QTreeWidgetItem *item_2 = tree->topLevelItem(1)->child(0)->child(0)->child(0)->child(0);
    if (item != NULL) {
        item->setText(TREE_VALUE, text);
        item_2->setText(TREE_VALUE, text);
        item->setTextColor(TREE_VALUE, Qt::red);
        item_2->setTextColor(TREE_VALUE, Qt::red);
    }
}

void EpromManager::scrollTree(QTreeWidgetItem *item) {
    ui->treeWidget->scrollToItem(item);
}

void EpromManager::scrollTree_2(QTreeWidgetItem *item) {
    ui->treeWidget_2->scrollToItem(item);
}

void EpromManager::closeEvent(QCloseEvent *event)
{
    //m_tcpClient = new TcpConnect();
    m_tcpClient->connectToServer();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    QString str = "Close";
    out<<quint16(0)<<str;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    m_tcpClient->sendRequest(block);
    GLO::delayms(20);

    if (m_isOpenCom)
    {
        onActionDisConnectClicked();
    }
    delete m_powerMap;
    delete m_controlMap;
    delete m_powerIndex;
    delete m_controlIndex;
    event->accept();
}

void EpromManager::receiveConfig(const QStringList &list) {
    m_modeName = list.at(0);
    m_typeName = list.at(1);
    m_comText = list.at(2);
    QString dspNum = list.at(3);
    m_dspNum = dspNum.toInt();
    qDebug()<<"mode"<<m_modeName;
    qDebug()<<"type"<<m_typeName;
    ui->comLabel->setText(m_comText);
    this->setWindowTitle(this->windowTitle() + "-" + m_modeName);
    m_tcpClient->stopConnection();
    //delete m_tcpClient;
}
