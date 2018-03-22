#include "comparisondialog.h"
#include "ui_comparisondialog.h"
#include "gtutils.h"
#include "qttreemanager.h"
#include <QSettings>
#include <QDebug>
#include <QTreeWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QAbstractSlider>

enum TREE{
    TREE_NAME = 0,
    TREE_VALUE = 1,
};

ComparisonDialog::ComparisonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComparisonDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    initPath();
    m_newLoaded = false;
    m_oldLoaded = false;
    m_editedItem = NULL;
    ui->progressBar_comp->hide();
    ui->btn_compComp->setEnabled(false);
    ui->btn_compUpdate->setEnabled(false);
    connect(ui->btn_compOld, SIGNAL(clicked()), this, SLOT(onActionOldBtnClicked()));
    connect(ui->btn_compNew, SIGNAL(clicked()), this, SLOT(onActionNewBtnClicked()));
    connect(ui->btn_compComp, SIGNAL(clicked()), this, SLOT(onActionCompareClicked()));
    connect(ui->btn_compUpdate, SIGNAL(clicked()), this, SLOT(onActionUpdateClicked()));
    connect(ui->btn_compSave, SIGNAL(clicked()), this, SLOT(onActionSaveClicked()));
    connect(ui->treeWidget_compNew, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onActionItemDoubleClicked(QTreeWidgetItem*,int)));
    connect(ui->treeWidget_compNew, SIGNAL(itemSelectionChanged()), this, SLOT(onActionEditFinished()));
    connect(ui->checkBox_compSync, SIGNAL(stateChanged(int)), this, SLOT(onActionSyncBoxChanged()));
}

ComparisonDialog::~ComparisonDialog()
{
    delete ui;
}

void ComparisonDialog::initPath()
{
    QString iniPath = GTUtils::customPath() + "option/opt.ini";
    QSettings settings(iniPath, QSettings::IniFormat);
    QVariant vd;
    settings.beginGroup("path");
    vd = settings.value("oldfilepath", ".");
    m_oldFilePath = vd.toString();
    if (m_oldFilePath.compare("") == 0) {
        m_oldFilePath = ".";
    }
    vd = settings.value("newfilepath", ".");
    m_newFilePath = vd.toString();
    if (m_newFilePath.compare("") == 0) {
        m_newFilePath = ".";
    }
}

void ComparisonDialog::onActionOldBtnClicked()
{
    ui->btn_compUpdate->setEnabled(false);
    m_oldItemList.clear();
    QString path = QFileDialog::getOpenFileName(this, tr("Open Old XML File"), m_oldFilePath, tr("Files(*.ui *.xml)"));
    if (path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You did not select any files."));
    } else {
        //QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
        m_oldFileInfo.setFile(path);
        m_oldFilePath = m_oldFileInfo.filePath() + "/";
        ui->treeWidget_compOld->clear();
        loadTree(path, ui->treeWidget_compOld);
        ui->treeWidget_compOld->expandAll();
        m_oldLoaded = true;
    }
    if (m_oldLoaded && m_newLoaded) {
        ui->btn_compComp->setEnabled(true);
    }
}

void ComparisonDialog::onActionNewBtnClicked()
{
    ui->btn_compUpdate->setEnabled(false);
    m_newItemList.clear();
    QString path = QFileDialog::getOpenFileName(this, tr("Open New XML File"), m_newFilePath, tr("Files(*.ui *.xml)"));
    if (path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You did not select any files."));
    } else {
        //QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
        m_newFileInfo.setFile(path);
        m_newFilePath = m_newFileInfo.filePath() + "/";
        ui->treeWidget_compNew->clear();
        loadTree(path, ui->treeWidget_compNew);
        ui->treeWidget_compNew->expandAll();
        m_newLoaded = true;
    }
    if (m_oldLoaded && m_newLoaded) {
        ui->btn_compComp->setEnabled(true);
    }
}

bool ComparisonDialog::loadTree(QString &path, QTreeWidget *treeWidget)
{
    QTreeWidget *tree = NULL;
    tree = QtTreeManager::createTreeWidgetFromXmlFile(path);;
    if(treeWidget == NULL)
        return false;
    else {
        QTreeWidgetItem *item;
        for(int i = 0;i < tree->topLevelItemCount(); i++)
        {
            item = tree->topLevelItem(i)->clone();
            treeWidget->addTopLevelItem(item);
        }
        item = tree->headerItem()->clone();
        treeWidget->setHeaderItem(item);
        tree->clear();
        delete tree;
        return true;
    }
}

void ComparisonDialog::onActionCompareClicked() {
    QTreeWidgetItem *oldNode = ui->treeWidget_compOld->invisibleRootItem();
    QTreeWidgetItem *newNode = ui->treeWidget_compNew->invisibleRootItem();
    ui->progressBar_comp->show();
    m_barCount = 0;
    ui->progressBar_comp->setValue(m_barCount);
    restoreItemList(m_oldItemList);
    restoreItemList(m_newItemList);
    m_oldItemList.clear();
    m_newItemList.clear();
    compareNode(oldNode, newNode);
    ui->progressBar_comp->hide();
    //QMessageBox::information(this, "Compare", "Finish!", QMessageBox::Ok);
    if (m_oldItemList.count() != 0 && m_newItemList.count() != 0) {
        ui->btn_compUpdate->setEnabled(true);
    }
}

void ComparisonDialog::onActionUpdateClicked()
{
    ui->progressBar_comp->setValue(0);
    ui->progressBar_comp->show();
    for (int i = 0; i < m_oldItemList.count(); i++) {
//        qDebug()<<"old text"<<m_oldItemList.at(i)->text(1);
//        qDebug()<<"new text"<<m_newItemList.at(i)->text(1);
        ui->progressBar_comp->setValue(i / m_oldItemList.count());
        for (int j = 1; j < qMin(m_newItemList.count(), m_oldItemList.count()); j++) {
            m_newItemList.at(i)->setText(j, m_oldItemList.at(i)->text(j));
        }
    }
    ui->progressBar_comp->hide();
}

void ComparisonDialog::onActionSaveClicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), m_newFilePath, tr("Files(*.ui)"));
    if (path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You did not select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
        m_newFileInfo.setFile(path);
        m_newFilePath = m_newFileInfo.filePath() + "/";
        QTreeWidget *tree = new QTreeWidget;
        QTreeWidgetItem *item;
        for(int i = 0; i < ui->treeWidget_compNew->topLevelItemCount(); i++)
        {
            item = ui->treeWidget_compNew->topLevelItem(i)->clone();
            tree->addTopLevelItem(item);
        }
        item = ui->treeWidget_compNew->headerItem()->clone();
        tree->setHeaderItem(item);
        eliminateEmptyItem(tree);
        QtTreeManager::writeTreeWidgetToXmlFile(path, tree);
        delete tree;
    }
}

void ComparisonDialog::onActionItemDoubleClicked(QTreeWidgetItem *item, int col)
{
    if (col != TREE_NAME) {
        if (ui->checkBox_compEdit->isChecked()) {
           ui->treeWidget_compNew->openPersistentEditor(item, col);
        }
        m_editedItem = item;
        m_editedCol = col;
    }
}

void ComparisonDialog::onActionEditFinished()
{
    if (m_editedItem != NULL) {
        ui->treeWidget_compNew->closePersistentEditor(m_editedItem, m_editedCol);
    }
}

void ComparisonDialog::onActionSyncBoxChanged()
{
    QAbstractScrollArea *area1 = ui->treeWidget_compNew;
    QAbstractScrollArea *area2 = ui->treeWidget_compOld;
    QAbstractSlider *sa1 = area1->verticalScrollBar();
    QAbstractSlider *sa2 = area2->verticalScrollBar();
    if(ui->checkBox_compSync->isChecked())
    {
        connect(sa1, SIGNAL(valueChanged(int)), sa2, SLOT(setValue(int)));
        connect(sa2, SIGNAL(valueChanged(int)), sa1, SLOT(setValue(int)));
    }
    else
    {
        disconnect(sa1, SIGNAL(valueChanged(int)), sa2, SLOT(setValue(int)));
        disconnect(sa2, SIGNAL(valueChanged(int)), sa1, SLOT(setValue(int)));
    }
}

void ComparisonDialog::compareNode(QTreeWidgetItem *oldNode, QTreeWidgetItem *newNode) {
    m_barCount += 1;
    if (m_barCount % 10 == 0) {
        ui->progressBar_comp->setValue(m_barCount % 100);
    }
    for (int i = 0; i < newNode->childCount(); i++) {
        bool exist = false;
        bool change = false;
        QString newNodeName = newNode->child(i)->text(TREE_NAME);
        for (int j = 0; j < oldNode->childCount(); j++) {
            QString oldNodeName = oldNode->child(j)->text(TREE_NAME);
            if (oldNodeName.compare("") != 0 && newNodeName.compare(oldNodeName) == 0) {
                exist = true;
                for (int k = 1; k < qMax(newNode->columnCount(), oldNode->columnCount()); k++) {
                    if (newNode->child(i)->text(k).compare(oldNode->child(j)->text(k)) != 0) {
                        change = true;
                        newNode->child(i)->setTextColor(k, Qt::red);
                        oldNode->child(j)->setTextColor(k, Qt::red);
                        m_newItemList.append(newNode->child(i));
                        m_oldItemList.append(oldNode->child(j));
                    }
                }
                if (change) {
                    for (int t = 0; t < oldNode->child(j)->columnCount(); t++) {
                        oldNode->child(j)->setBackgroundColor(t, Qt::yellow);
                    }
                    for (int t = 0; t < newNode->child(i)->columnCount(); t++) {
                        newNode->child(i)->setBackgroundColor(t, Qt::yellow);
                    }
                }
                compareNode(oldNode->child(j), newNode->child(i));
                break;
            }
        }
        if (!exist && newNodeName.compare("") != 0) {
            //qDebug()<<"new"<<newNodeName;
            for (int t = 0; t < newNode->child(i)->columnCount(); t++) {
                //newNode->child(i)->setBackgroundColor(t, Qt::green);
                QStringList itemList;
                for (int ii = 0; ii < oldNode->columnCount(); ii++) {
                    itemList.append("");
                }
                oldNode->insertChild(i, new QTreeWidgetItem(itemList));
            }
        }
    }
    for (int i = 0; i < oldNode->childCount(); i++) {
        bool exist = false;
        QString oldNodeName = oldNode->child(i)->text(TREE_NAME);
        for (int j = 0; j < newNode->childCount(); j++) {
            QString newNodeName = newNode->child(j)->text(TREE_NAME);
            if (newNodeName.compare("") != 0 && newNodeName.compare(oldNodeName) == 0) {
                exist = true;
                break;
            }
        }
        if (!exist && oldNodeName.compare("") != 0) {
            //qDebug()<<"old"<<oldNodeName;
            for (int t = 0; t < oldNode->child(i)->columnCount(); t++) {
                //oldNode->child(i)->setBackgroundColor(t, Qt::red);
                QStringList itemList;
                for (int ii = 0; ii < newNode->columnCount(); ii++) {
                    itemList.append("");
                }
                newNode->insertChild(i, new QTreeWidgetItem(itemList));
            }
        }
    }
}

void ComparisonDialog::eliminateEmptyItem(QTreeWidget *tree)
{
    clearEmptyItem(tree->invisibleRootItem());
}

void ComparisonDialog::clearEmptyItem(QTreeWidgetItem *item)
{
    for (int i = item->childCount() - 1; i >= 0; i--) {
        QTreeWidgetItem *childItem = item->child(i);
        if (childItem->text(TREE_NAME).compare("") == 0) {
            item->removeChild(childItem);
        } else {
            clearEmptyItem(childItem);
        }
    }
}

void ComparisonDialog::restoreItemList(QList<QTreeWidgetItem *> list)
{
    QTreeWidgetItem *item;
    for (int i = 0; i < list.count(); i++) {
        item = list.at(i);
        for (int j = 0; j < item->columnCount(); j++) {
            item->setTextColor(j, Qt::black);
            item->setBackgroundColor(j, Qt::white);
        }
    }
}

