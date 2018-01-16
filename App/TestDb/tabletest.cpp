#include "tabletest.h"
#include "ui_tabletest.h"
#include <QDebug>
#include <QSignalMapper>
#include <QComboBox>
#include <QSqlRecord>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHBoxLayout>

tableTest::tableTest(QWidget *parent, QString role, DBManager *manager) :
    QDialog(parent),
    ui(new Ui::tableTest)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);
    m_role = role;
    m_dbManager = manager;
    m_isOpenCom = false;
    m_type = GTSD_COM_TYPE_RNNET;
    ui->disconnectButton->setEnabled(false);
    ui->readButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    showRoles();
    connect(ui->roleList, SIGNAL(currentRowChanged(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onActionAddClicked()));
    //connect(ui->roleList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(onActionItemChanged(QListWidgetItem*)));
    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(onActionConfirmClicked()));
    //addButtonOnList();

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onActionConnectClicked()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(onActionDisConnectClicked()));
    connect(ui->readButton, SIGNAL(clicked()), this, SLOT(onActionReadClicked()));
    connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(onActionCheckClicked()));
}

tableTest::~tableTest()
{
    delete ui;
}

void tableTest::showRoles() {
    QStringList list = m_dbManager->readSingleTable(m_role);
    ui->roleLabel->setText(m_role);
    ui->roleList->addItems(list);
    modifyWidgetsAmount(ui->roleList->count());
    ui->roleList->setCurrentItem(ui->roleList->item(0));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(onActionDeleteTriggered()));
    //ui->roleList->setContextMenuPolicy(Qt::CustomContextMenu);
    //setMenu(ui->roleList);
    //connect(ui->roleList, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(showListWidgetMenuSlot(QPoint)));
    m_modelList = m_dbManager->getRoleModels(m_role);
    for (int i = 0; i < ui->stackedWidget->count(); i++) {
        showWidget(i);
    }
}



//void tableTest::showListWidgetMenuSlot(QPoint pos)
//{
//    m_contextMenu->exec(QCursor::pos());
//}

void tableTest::showWidget(int index) {
    QHBoxLayout* hBox = new QHBoxLayout;
    QSignalMapper *pMapperRemove = new QSignalMapper();
    QSignalMapper *pMapperAdd = new QSignalMapper();
    for (int i = 0; i < m_modelList.count(); i++) {
        QSqlTableModel *model = m_modelList.at(i);
        QVBoxLayout* vBox = new QVBoxLayout;
        QListWidget* singleList = new QListWidget(this);
        QLabel* textLabel = new QLabel(this);
        QPushButton* addButton = new QPushButton(tr("Add"));
        QPushButton* removeButton = new QPushButton(tr("Remove"));
        QListWidget* supportList = new QListWidget(this);
        QString title = getTitle(model);
        QStringList singleModel = m_dbManager->readSingleTable(title);
        textLabel->setText(title);
        singleList->addItems(singleModel);
        singleList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        for (int j = 0; j < model->rowCount(); j++) {
            QSqlRecord record = model->record(j);
            QString str = record.value(m_role).toString();
            if (str.compare(ui->roleList->item(index)->text()) == 0) {
                QString text = record.value(getTitle(model)).toString();
                supportList->addItem(text);
            }
        }
        vBox->addWidget(textLabel);
        vBox->addWidget(singleList);
        vBox->addWidget(addButton);
        vBox->addWidget(supportList);
        vBox->addWidget(removeButton);
        connect(addButton, SIGNAL(clicked()), pMapperAdd, SLOT(map()));
        pMapperAdd->setMapping(addButton, i);
        connect(removeButton, SIGNAL(clicked()), pMapperRemove, SLOT(map()));
        pMapperRemove->setMapping(removeButton, i);
        hBox->addLayout(vBox);
    }
    connect(pMapperRemove, SIGNAL(mapped(int)), this, SLOT(onActionSupportItemDelete(int)));
    connect(pMapperAdd, SIGNAL(mapped(int)), this, SLOT(onActionSupportItemAdd(int)));
    ui->stackedWidget->widget(index)->setLayout(hBox);
}

//void tableTest::showRoles() {
//    QStringList list = m_dbManager->readSingleTable(m_role);
//    ui->roleLabel->setText(m_role);
//    ui->roleList->addItems(list);
//    modifyWidgetsAmount(ui->roleList->count());
//    ui->roleList->setCurrentItem(ui->roleList->item(0));
//    m_modelList = m_dbManager->getRoleModels(m_role);
//    for (int i = 0; i < ui->stackedWidget->count(); i++) {
//        QList<QGroupBox*> groupList = getGroupList(ui->stackedWidget->widget(i));
//        showWidget(groupList, i);
//    }
//}
//
//QList<QGroupBox*> tableTest::getGroupList(QWidget *widget) {
//    QHBoxLayout *hBox = new QHBoxLayout;
//    QList<QGroupBox*> groupList;
//    QSignalMapper *pMapper = new QSignalMapper();
//    for (int i = 0; i < m_modelList.count(); i++) {
//        QPushButton *button = new QPushButton(tr("Add"));
//        QVBoxLayout *vBox = new QVBoxLayout;
//        QSqlTableModel *model = m_modelList.at(i);
//        QString title = getTitle(model);
//        QGroupBox* tableBox = new QGroupBox(title);
//        groupList.append(tableBox);
//        vBox->addWidget(groupList.at(i));
//        vBox->addWidget(button);
//        hBox->addLayout(vBox);
//        connect(button, SIGNAL(clicked()), pMapper, SLOT(map()));
//        pMapper->setMapping(button, i);
//    }
//    connect(pMapper, SIGNAL(mapped(int)), this, SLOT(onActionAddExistedClicked(int)));
//    widget->setLayout(hBox);
//    return groupList;
//}

//void tableTest::showWidget(QList<QGroupBox*> groupList, int index) {
//    for (int i = 0; i < groupList.count(); i++) {
//        if (groupList.at(i)->layout() == 0) {
//            groupList.at(i)->setLayout(new QVBoxLayout);
//        }
//        while (groupList.at(i)->layout()->count()) {
//            QWidget *q = groupList.at(i)->layout()->itemAt(0)->widget();
//            q->setParent(NULL);
//            groupList.at(i)->layout()->removeWidget(q);
//            delete q;
//        }
//    }
//    QString itemName = ui->roleList->item(index)->text();
//    for (int i = 0; i < m_modelList.count(); i++) {
//        QSqlTableModel *model = m_modelList.at(i);
//        for (int j = 0; j < model->rowCount(); j++) {
//            QSqlRecord record = model->record(j);
//            QString str = record.value(m_role).toString();
//            if (str.compare(itemName) == 0) {
//                QString checkBoxName = record.value(getTitle(model)).toString();
//                QCheckBox *checkBox = new QCheckBox(checkBoxName);
//                checkBox->setChecked(true);
//                groupList.at(i)->layout()->addWidget(checkBox);
//            }
//        }
//    }
//}


QString tableTest::getTitle(QSqlTableModel *model) {
    QString strOne = model->tableName().at(8);
    QString strTwo = model->tableName().at(9);
    QString title;
    if (strOne.compare(m_role) == 0) {
        title = strTwo;
    } else {
        title = strOne;
    }
    return title;
}

void tableTest::onActionAddClicked() {
    QString itemText = ui->addLine->text();
    if (itemText == "") {
        return;
    }
    for (int i = 0; i < ui->roleList->count(); i++) {
        QString text = ui->roleList->item(i)->text();
        if (text.compare(itemText) == 0) {
            QMessageBox::warning(this, tr("Warning"), tr("This code has already existed!"), QMessageBox::Ok);
            return;
        }
    }
    QListWidgetItem *item = new QListWidgetItem(itemText);
    ui->roleList->insertItem(ui->roleList->count(), item);
    modifyWidgetsAmount(ui->roleList->count());
    ui->roleList->setCurrentItem(item);
    int index = ui->roleList->currentRow();
    showWidget(index);
    ui->addLine->clear();
    m_dbManager->addSingle(m_role, itemText);
//    QListWidgetItem *item = new QListWidgetItem("New Item");
//    item->setFlags(item->flags() | Qt::ItemIsEditable);
//    ui->roleList->insertItem(ui->roleList->count(), item);
//    modifyWidgetsAmount(ui->roleList->count());
//    ui->roleList->editItem(item);
//    ui->roleList->setCurrentItem(item);
//    int index = ui->roleList->currentRow();
//    showWidget(index);
}

//void tableTest::addButtonOnList() {
//    QListWidgetItem *item = new QListWidgetItem;
//    QPushButton* newButton = new QPushButton("Add");
//    newButton->setAutoDefault(false);
//    ui->roleList->addItem(item);
//    ui->roleList->setItemWidget(item, newButton);
//    connect(newButton, SIGNAL(clicked()), this, SLOT(onActionAddClicked()));
//}

void tableTest::modifyWidgetsAmount(int num) {
    if (num < 0) {
        return;
    }
    while (ui->stackedWidget->count() < num) {
        ui->stackedWidget->count();
        QWidget *widget = new QWidget(this);
        ui->stackedWidget->addWidget(widget);
    }
    while (ui->stackedWidget->count() > num) {
        QWidget* widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

//void tableTest::onActionItemChanged(QListWidgetItem* item) {
//    ui->roleList->setCurrentItem(item);
//    int index = ui->roleList->currentRow();
//    QString text = item->text();
//    for (int i = 0; i < ui->roleList->count(); i++) {
//        if (index != i) {
//            QString itemText = ui->roleList->item(i)->text();
//            if (text.compare(itemText) == 0 && text.compare("New Item") != 0) {
//                QMessageBox::warning(this, tr("Warning"), tr("This code has already existed!"), QMessageBox::Ok);
//                item->setText(tr("New Item"));
//                return;
//            }
//        }
//    }
//}

//void tableTest::contextMenuEvent(QContextMenuEvent *event) {
//    QMenu* popMenu = new QMenu(ui->roleList);
//    QAction *deleteAction = new QAction(tr("Delete"), ui->roleList);
//    QPoint point = ui->roleList->mapFromGlobal(QCursor::pos());
//    QListWidgetItem *item = ui->roleList->itemAt(point);
//    ui->roleList->setCurrentItem(item);
//    connect(deleteAction, SIGNAL(triggered()), this, SLOT(onActionDeleteTriggered()));
//    if (item != NULL)
//    {
//        popMenu->addAction(deleteAction);
//    }
//    popMenu->exec(QCursor::pos());
//    delete popMenu;
//    delete deleteAction;
//}

void tableTest::onActionDeleteTriggered() {
    QListWidgetItem *item = ui->roleList->currentItem();
    int ret = QMessageBox::question(this, tr("Question"), tr("Are you sure to delete ") + item->text() + "?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    if (item == NULL) {
        return;
    }
    onActionSupportItemClear();
    int curIndex = ui->roleList->currentRow();
    ui->roleList->takeItem(curIndex);
    QWidget *widget = ui->stackedWidget->widget(curIndex);
    if (widget == NULL) {
        return;
    }
    ui->stackedWidget->removeWidget(widget);
    delete widget;
    m_dbManager->deleteSingle(m_role, item->text());
    delete item;
}

void tableTest::onActionSupportItemDelete(int index) {
    QWidget *supportWidget = ui->stackedWidget->currentWidget()->layout()->layout()->itemAt(index)->layout()->itemAt(3)->widget();
    QListWidget *supportList = static_cast<QListWidget*>(supportWidget);
    QListWidgetItem *item = supportList->currentItem();
    if (item == NULL) {
        return;
    }
    int ret = QMessageBox::question(this, tr("Question"), tr("Are you sure to delete ") + item->text() + "?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    int curIndex = supportList->currentRow();
    supportList->takeItem(curIndex);
    QWidget *textWidget = ui->stackedWidget->currentWidget()->layout()->layout()->itemAt(index)->layout()->itemAt(0)->widget();
    QLabel *textLabel = static_cast<QLabel*>(textWidget);
    QString secondRole = textLabel->text();
    QString str = ui->roleList->currentItem()->text() + "-" + item->text();
    m_dbManager->deleteRelation(m_role, secondRole, str);
    delete item;
}

void tableTest::onActionSupportItemClear() {
    for (int i = 0; i < m_modelList.count(); i++) {
        QWidget *supportWidget = ui->stackedWidget->currentWidget()->layout()->layout()->itemAt(i)->layout()->itemAt(3)->widget();
        QListWidget *supportList = static_cast<QListWidget*>(supportWidget);
        QWidget *textWidget = ui->stackedWidget->currentWidget()->layout()->layout()->itemAt(i)->layout()->itemAt(0)->widget();
        QLabel *textLabel = static_cast<QLabel*>(textWidget);
        QString secondRole = textLabel->text();
        while(supportList->count() > 0) {
            QListWidgetItem *item = supportList->item(0);
            QString str = ui->roleList->currentItem()->text() + "-" + item->text();
            m_dbManager->deleteRelation(m_role, secondRole, str);
            delete item;
        }
    }
}

void tableTest::onActionSupportItemAdd(int index) {
    QWidget *supportWidget = ui->stackedWidget->currentWidget()->layout()->layout()->itemAt(index)->layout()->itemAt(3)->widget();
    QListWidget *supportList = static_cast<QListWidget*>(supportWidget);
    QWidget *singleWidget = ui->stackedWidget->currentWidget()->layout()->layout()->itemAt(index)->layout()->itemAt(1)->widget();
    QListWidget *singleList = static_cast<QListWidget*>(singleWidget);
    QList<QListWidgetItem*> items = singleList->selectedItems();
    int ret = QMessageBox::question(this, tr("Question"), tr("Are you sure to add these items?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::No) {
        return;
    }
    QStringList* strList = new QStringList;
    for (int i = 0; i < items.count(); i++) {
        strList->append(items.at(i)->text());
    }
    deleteDuplicatedItems(strList, supportList);
    supportList->addItems(*strList);

    QWidget *textWidget = ui->stackedWidget->currentWidget()->layout()->layout()->itemAt(index)->layout()->itemAt(0)->widget();
    QLabel *textLabel = static_cast<QLabel*>(textWidget);
    QString secondRole = textLabel->text();
    QStringList relationList;
    QString strOne = ui->roleList->currentItem()->text();
    for (int i = 0; i < strList->count(); i++) {
        QString str = strOne + "-" + strList->at(i);
        relationList.append(str);
    }
    m_dbManager->addRelation(m_role, secondRole, relationList);
}

void tableTest::deleteDuplicatedItems(QStringList* strList, QListWidget *supportList) {
    for (int i = 0; i < supportList->count(); i++) {
        QString supportStr = supportList->item(i)->text();
        for (int j = 0; j < strList->count(); j++) {
            QString str = strList->at(j);
            if (str.compare(supportStr) == 0) {
                strList->removeOne(str);
                break;
            }
        }
    }
}

//void tableTest::onActionAddExistedClicked(int index) {
//    LinkAddition *linkAdditionDialog = new LinkAddition(this, index, m_role, ui->roleList->currentItem()->text(), m_dbManager, ui->roleList->currentRow());
//    connect(linkAdditionDialog, SIGNAL(okSignal(QList<QCheckBox*>, int, int)), this, SLOT(onAdditionReceived(QList<QCheckBox*>, int, int)));
//    linkAdditionDialog->exec();
//    delete linkAdditionDialog;
//}

//void tableTest::onAdditionReceived(QList<QCheckBox *> boxList, int index, int currentIndex) {
//    for (int i = 0; i < boxList.count(); i++) {
//        ui->stackedWidget->widget(currentIndex)->layout()->itemAt(index)->layout()->itemAt(0)->widget()->layout()->addWidget(boxList.at(i));
//    }
//}

void tableTest::onActionConfirmClicked() {
    //writeSingle();
    //writeRelation();
    m_dbManager->writeSummary();
}

//void tableTest::writeSingle() {
//    QStringList singleList;
//    for (int i = 0; i < ui->roleList->count(); i++) {
//        QString str = ui->roleList->item(i)->text();
//        singleList.append(str);
//    }
//    m_dbManager->writeSingle(m_role, singleList);
//}

//void tableTest::writeRelation() {
//    for (int i = 0; i < m_modelList.count(); i++) {
//        QWidget *textWidget = ui->stackedWidget->widget(i)->layout()->layout()->itemAt(i)->layout()->itemAt(0)->widget();
//        QLabel *textLabel = static_cast<QLabel*>(textWidget);
//        QString secondRole = textLabel->text();
//        QStringList relationList;
//        for (int j = 0; j < ui->roleList->count(); j++) {
//            QString strOne = ui->roleList->item(j)->text();
//            QWidget *supportWidget = ui->stackedWidget->widget(j)->layout()->layout()->itemAt(i)->layout()->itemAt(3)->widget();
//            QListWidget *supportList = static_cast<QListWidget*>(supportWidget);
//            for (int k = 0; k < supportList->count(); k++) {
//                QString strTwo = supportList->item(k)->text();
//                QString str = strOne + "-" + strTwo;
//                relationList.append(str);
//            }
//        }
//        m_dbManager->writeRelation(m_role, secondRole, relationList);
//    }
//}

void tableTest::onActionConnectClicked() {
        COM_ERROR error = COM_OK;
        error = static_cast<COM_ERROR>(GTSD_CMD_Open(updateProgessBar, (void*)0, m_type));
        if (error != COM_OK) {
            GTSD_CMD_Close(m_type);
            m_isOpenCom = false;
            QMessageBox::warning(this, tr("Warning"), tr("Connection Failed!"), QMessageBox::Ok);
        } else {
            ui->connectButton->setEnabled(false);
            ui->readButton->setEnabled(true);
            ui->disconnectButton->setEnabled(true);
            ui->checkButton->setEnabled(true);
            m_isOpenCom = true;
            QString m_powerPath = "./Resources/File/PB/M/M4/series1/SD43P003/SD43P003.ui";
            QString m_controlPath = "./Resources/File/CB/M/M4/Series1/SD43P003/SD43P003.ui";
            powerBoard = new EPROM_POWER(m_powerPath, m_type);
            controlBoard = new EPROM_CONTROL(m_controlPath, m_type);
        }
}

void tableTest::onActionDisConnectClicked() {
    if (m_isOpenCom) {
        GTSD_CMD_Close(m_type);
        m_isOpenCom = false;
        ui->readButton->setEnabled(false);
        ui->disconnectButton->setEnabled(false);
        ui->connectButton->setEnabled(true);
        ui->checkButton->setEnabled(false);
        ui->cLine->clear();
        ui->pLine->clear();
        ui->vLine->clear();
        ui->fLine->clear();
        delete powerBoard;
        delete controlBoard;
    }
}

void tableTest::updateProgessBar(void *arg, qint16 *value)
{
//    QProgressBar *bar = static_cast<QProgressBar *>(arg);
//    bar->setValue(*value);
//    qApp->processEvents();
    //qDebug()<<"value "<<*value;
}

void tableTest::onActionReadClicked() {
    Uint32 powerID = powerBoard->readID();
    QString pID = QString::number(powerID, 10);
    qDebug()<<"pID"<<pID;
    ui->pLine->setText(pID);
    Uint32 controlID = controlBoard->readID();
    QString cID = QString::number(controlID, 10);
    qDebug()<<"cID"<<cID;
    ui->cLine->setText(cID);
    Uint16 ver1;
    int16 ret1 = GTSD_CMD_ReadProcessorVersion(0, ver1, m_type, 0xf0);
    qDebug()<<"ret1 ="<<ret1;
    QString vID = QString::number(ver1, 10);
    qDebug()<<"vID"<<vID;
    ui->vLine->setText(vID);
    VERSION ver2;
    qDebug()<<"aa";
    int16 ret2 = GTSD_CMD_ReadFpgaVersion(0, &ver2, m_type, 0xf0);
    qDebug()<<"ret2 ="<<ret2;
    QString fID = QString::number(ver2.usVersion, 10);
    qDebug()<<"fID"<<fID;
    ui->fLine->setText(fID);
}

void tableTest::onActionCheckClicked() {
    QStringList list;
    list.append(ui->cLine->text());
    list.append(ui->vLine->text());
    list.append(ui->fLine->text());
    list.append(ui->pLine->text());
    bool result = m_dbManager->checkValid(list);
    if (result) {
        ui->checkLine->setText(tr("Valid!"));
    } else {
        ui->checkLine->setText(tr("Invalid!"));
    }
}
