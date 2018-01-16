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



EpromManager::EpromManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EpromManager)
{
    ui->setupUi(this);
    m_filePath = ".";
    tcpClient = NULL;
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    ui->list->item(0)->setIcon(QIcon(ICON_FILE_PATH + "Select.png"));
    ui->list->item(1)->setIcon(QIcon(ICON_FILE_PATH + "menu_restoresetting.png"));
    ui->list->item(2)->setIcon(QIcon(ICON_FILE_PATH + "Power.png"));
    ui->list->item(3)->setIcon(QIcon(ICON_FILE_PATH + "Control.png"));
    connect(ui->list, SIGNAL(currentRowChanged(int)), ui->stack, SLOT(setCurrentIndex(int)));
    ui->RNNetButton->setChecked(true);
    initializeTree();
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
    connect(ui->RNNetButton, SIGNAL(clicked()), this, SLOT(onComButtonClicked()));
    connect(ui->PCDebugButton, SIGNAL(clicked()), this, SLOT(onComButtonClicked()));


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

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onActionConnectToServer()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(onActionStopConnection()));
}

EpromManager::~EpromManager()
{
    delete ui;
}

void EpromManager::initializeTree() {
    ui->progressBar->hide();    
    showSelectTree();
    ui->selectTree->topLevelItem(0)->child(0)->setSelected(true);
    powerIndex = TreeManager::createTreeWidgetFromXmlFile(RESOURCE_FILE_PATH + "PB/pbindex.ui");
    controlIndex = TreeManager::createTreeWidgetFromXmlFile(RESOURCE_FILE_PATH + "CB/cbindex.ui");
    powerMap = TreeManager::createTreeWidgetFromXmlFile(RESOURCE_FILE_PATH + "IdMap_Power.ui");
    controlMap = TreeManager::createTreeWidgetFromXmlFile(RESOURCE_FILE_PATH + "IdMap_Control.ui");
    treeItemClicked(ui->selectTree->topLevelItem(0)->child(0), 0);
    onComButtonClicked();
    //qDebug()<<m_configText;
    //qDebug()<<m_comText;
}

com_type EpromManager::getComType() {
    if (ui->RNNetButton->isChecked()) {
        return GTSD_COM_TYPE_RNNET;
    } else {
        return GTSD_COM_TYPE_NET;
    }
}

void EpromManager::onBarUpdate() {
    barCount++;
    if (barCount % 10 == 0) {
        ui->progressBar->setValue(barCount % 100);
    }
}

void EpromManager::showWarn(QString msg) {
    ui->warnLabel->setText(msg);
}

void EpromManager::setBarCount(int value) {
    barCount = value;
    if (barCount % 10 == 0) {
        ui->progressBar->setValue(barCount % 100);
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
    showTree(m_powerID, powerBoard->getTree(), ui->treeWidget);
    showTree(m_controlID, controlBoard->getTree(), ui->treeWidget_2);
}

void EpromManager::showSelectTree() {
    QTreeWidget *tree = TreeManager::createTreeWidgetFromXmlFile(RESOURCE_FILE_PATH + "SelectTree.ui");
    for (int i = 0; i < tree->topLevelItemCount(); i++) {
        ui->selectTree->addTopLevelItem(tree->topLevelItem(i)->clone());
    }
    ui->selectTree->expandAll();
    ui->selectTree->resizeColumnToContents(0);
    delete tree;
}

/**************************************************************/

/********************** write *************************/
void EpromManager::onWriteClicked() {
    QString typeText = ui->typeLabel->text();
    QString code = ui->lineEdit->text();
    if (code == "") {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter a PCBA code!"), QMessageBox::Ok);
        return;
    }
    int ret = QMessageBox::question(this, tr("Question"), tr("Are you sure to write\n") + typeText + "?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    ui->lineEdit->setReadOnly(true);
    ui->readButton->setEnabled(false);
    ui->warnLabel->clear();
    ui->progressBar->setRange(0, 100);
    ui->progressBar->show();
    barCount = 0;
    ui->progressBar->setValue(barCount);
    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(0);
    powerBoard->writeFromXmltoEprom(item);
    ui->progressBar->hide();
    ui->lineEdit->setReadOnly(false);
    ui->readButton->setEnabled(true);
}

void EpromManager::onWriteClicked_2() {
    QString typeText = ui->typeLabel->text();
    QString code = ui->lineEdit_2->text();
    if (code == "") {
        QMessageBox::warning(this, tr("Warning"), tr("Please enter a PCBA code!"), QMessageBox::Ok);
        return;
    }
    int ret = QMessageBox::question(this, tr("Question"), tr("Are you sure to write\n") + typeText + "?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    ui->lineEdit_2->setReadOnly(true);
    ui->readButton_2->setEnabled(false);
    ui->warnLabel->clear();
    ui->progressBar->setRange(0, 100);
    ui->progressBar->show();
    barCount = 0;
    ui->progressBar->setValue(barCount);
    QTreeWidgetItem *item = ui->treeWidget_2->topLevelItem(0);
    controlBoard->writeFromXmltoEprom(item);
    ui->progressBar->hide();
    ui->lineEdit_2->setReadOnly(false);
    ui->readButton_2->setEnabled(true);
}

void EpromManager::treeItemClicked(QTreeWidgetItem* item, int column) {
    itemText = item->text(column);
    if (item->childCount() == 0) {
        QTreeWidgetItem *controlItem = GLO::findItem(itemText, controlMap, IDMAP_MODE);
        QTreeWidgetItem *powerItem = GLO::findItem(itemText, powerMap, IDMAP_MODE);
        m_powerID = powerItem->text(IDMAP_ID);
        m_controlID = controlItem->text(IDMAP_ID);
        m_dspNum = item->text(column + 1).toInt();
        QTreeWidgetItem *powerIndexItem = GLO::findItem(m_powerID, powerIndex, TREE_VALUE);
        QTreeWidgetItem *controlIndexItem = GLO::findItem(m_controlID, controlIndex, TREE_VALUE);
        m_powerPath = GLO::getPath(powerIndexItem);
        m_controlPath = GLO::getPath(controlIndexItem);
        m_powerPath = RESOURCE_FILE_PATH + "PB/" + m_powerPath;
        m_controlPath = RESOURCE_FILE_PATH + "CB/" + m_controlPath;
        //qDebug()<<m_powerPath;
        //qDebug()<<m_controlPath;
        //qDebug()<<m_dspNum;
        changeConfigText(m_powerID, powerIndex);
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

void EpromManager::onComButtonClicked() {
    if (ui->RNNetButton->isChecked()) {
        m_comText = "RNNet";
    } else {
        m_comText = "PCDebug";
    }
    showText(m_configText, m_comText);
}

void EpromManager::showText(QString configText, QString comText) {
    QString typeText = configText + "\n\n" + "Com Type:\n" + comText;
    ui->typeLabel->setText(typeText);
}


void EpromManager::showTree(QString text, QTreeWidget *tree, QTreeWidget *uiTree) {
    QTreeWidgetItem *item = GLO::findItem(text, tree, TREE_VALUE);
    uiTree->clear();
    uiTree->addTopLevelItem(item->clone());
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
    barCount = 0;
    ui->progressBar->setValue(0);
    powerBoard->readFromEprom(ui->readTreeWidget);
    ui->progressBar->hide();
    ui->compareButton->setEnabled(true);
}

void EpromManager::onReadClicked_2() {
    ui->readTreeWidget_2->clear();
    ui->warnLabel->clear();
    ui->progressBar->show();
    barCount = 0;
    ui->progressBar->setValue(0);
    controlBoard->readFromEprom(ui->readTreeWidget_2);
    ui->progressBar->hide();
    ui->compareButton_2->setEnabled(true);
}

/*******************************************************************************/

/**************************** compare ******************************************/
void EpromManager::onCompareClicked() {
    ui->warnLabel->clear();
    ui->progressBar->show();
    barCount = 0;
    ui->progressBar->setValue(barCount);
    powerBoard->compare(ui->readTreeWidget);
    ui->progressBar->hide();
}

void EpromManager::onCompareClicked_2() {
    ui->warnLabel->clear();
    ui->progressBar->show();
    barCount = 0;
    ui->progressBar->setValue(barCount);
    controlBoard->compare(ui->readTreeWidget_2);
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
            ui->connectIcon->setIcon(QIcon(ICON_FILE_PATH + ICON_STATUS_DISCONNECT));
            m_isOpenCom = false;
            QMessageBox::warning(this, tr("Warning"), tr("Connection Failed!"), QMessageBox::Ok);
        } else {
            ui->connectButton->setEnabled(false);
            ui->connectIcon->setIcon(QIcon(ICON_FILE_PATH + ICON_STATUS_CONNECT));
            m_isOpenCom = true;
            com_type comType = getComType();
            powerBoard = new EPROM_POWER(m_powerPath, comType);
            controlBoard = new EPROM_CONTROL(m_controlPath, comType);
            connect(powerBoard, SIGNAL(updateBarCount()), this, SLOT(onBarUpdate()));
            connect(powerBoard, SIGNAL(sendWarnMsg(QString)), this, SLOT(showWarn(QString)));
            connect(powerBoard, SIGNAL(changeBarCount(int)), this, SLOT(setBarCount(int)));
            connect(powerBoard, SIGNAL(sendScrollItem(QTreeWidgetItem*)), this, SLOT(scrollTree(QTreeWidgetItem*)));
            connect(controlBoard, SIGNAL(updateBarCount()), this, SLOT(onBarUpdate()));
            connect(controlBoard, SIGNAL(sendWarnMsg(QString)), this, SLOT(showWarn(QString)));
            connect(controlBoard, SIGNAL(changeBarCount(int)), this, SLOT(setBarCount(int)));
            connect(controlBoard, SIGNAL(sendScrollItem(QTreeWidgetItem*)), this, SLOT(scrollTree_2(QTreeWidgetItem*)));
            onOkClicked();
        }
        ui->progressBar->hide();
}

void EpromManager::onActionDisConnectClicked() {
    if (m_isOpenCom) {
        GTSD_CMD_Close(getComType());
        ui->connectIcon->setIcon(QIcon(ICON_FILE_PATH + ICON_STATUS_DISCONNECT));
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
        delete powerBoard;
        delete controlBoard;
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
        ui->connectIcon->setIcon(QIcon(ICON_FILE_PATH+ICON_STATUS_CONNECT));
        m_isOpenCom = true;
    }
    else
    {
        ui->connectIcon->setIcon(QIcon(ICON_FILE_PATH+ICON_STATUS_DISCONNECT));
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
    onTextChange(text, ui->treeWidget);
}

void EpromManager::onLineTextChange_2(QString text) {
    onTextChange(text, ui->treeWidget_2);
}

void EpromManager::onTextChange(QString text, QTreeWidget *tree) {
    QTreeWidgetItem *item = GLO::findItem("PCBA code", tree, TREE_NAME);
    if (item != NULL) {
        item->setText(TREE_VALUE, text);
        tree->topLevelItem(0)->setText(TREE_VALUE, text);
        item->setTextColor(TREE_VALUE, Qt::red);
        tree->topLevelItem(0)->setTextColor(TREE_VALUE, Qt::red);
    }
}

void EpromManager::scrollTree(QTreeWidgetItem *item) {
    ui->treeWidget->scrollToItem(item);
}

void EpromManager::scrollTree_2(QTreeWidgetItem *item) {
    ui->treeWidget_2->scrollToItem(item);
}

/************************Tcp Client ****************************************/

void EpromManager::onActionConnectToServer() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    QString str;
    if (getComType() == GTSD_COM_TYPE_RNNET) {
        str = "RNNET";
    } else {
        str = "PCDebug";
    }
    out<<quint16(0)<<str;
    out.device()->seek(0);
    out<<quint16(block.size() - sizeof(quint16));
    tcpClient = new TcpConnect(block);
    tcpClient->connectToServer();
}

void EpromManager::onActionStopConnection() {
    qDebug()<<"a";
    if (tcpClient != NULL) {
        tcpClient->stopConnection();
    }
    qDebug()<<"aa";
}

void EpromManager::closeEvent(QCloseEvent *event)
{
    if(m_isOpenCom)
    {
        onActionDisConnectClicked();
    }
    delete powerMap;
    delete controlMap;
    delete powerIndex;
    delete controlIndex;
    event->accept();
}
