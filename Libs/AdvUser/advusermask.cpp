#include "advusermask.h"
#include "ui_advusermask.h"
#include "iadvuser_p.h"
#include "gtutils.h"
#include "sdtglobaldef.h"
#include "bititemhelper.h"
#include "deviceconfig.h"
#include "qttreemanager.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include <QSignalMapper>
#include <QDebug>

#define ITEM_NAME_0 "gSevDrv.sev_obj.cur.pro.prm.alm_mask_flag"
#define INFORMATION_FILENAME "PrmFuncDeviceStatusAlarmInfo0.xml"
#define STR_MARK_ALL "all"
#define STR_MARK_BIT "bit"

class AdvUserMaskPrivate : public IAdvUserPrivate {
    Q_DECLARE_PUBLIC(AdvUserMask)
public:
    AdvUserMaskPrivate();
    ~AdvUserMaskPrivate();
    QList<SevDevice*> m_devList;
    QColor m_nodeColor;
    QList<QTreeWidgetItem*> m_changedItemList;
    QMenu *m_itemMenu;
    QList<QAction *>m_actionList;
};

AdvUserMaskPrivate::AdvUserMaskPrivate() {

}

AdvUserMaskPrivate::~AdvUserMaskPrivate() {

}

//class AdvMapperIndex : public QObject {
//public:
//    AdvMapperIndex();
//    ~AdvMapperIndex();
//    int m_devIndex;
//    int m_axisIndex;
//    int m_copyIndex;
//    QTreeWidgetItem *m_clickedItem;
//};

//AdvMapperIndex::AdvMapperIndex() {

//}

//AdvMapperIndex::~AdvMapperIndex() {

//}

AdvUserMask::AdvUserMask(const QString &advName, QWidget *parent) :
    IAdvUser(advName, *new AdvUserMaskPrivate, parent),
    ui(new Ui::AdvUserMask)
{
    Q_D(AdvUserMask);
    ui->setupUi(this);
    this->setFocus();
    d->m_nodeColor = Qt::blue;
    connect(ui->tree_advMask, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(onItemExpanded(QTreeWidgetItem*)));
    connect(ui->tree_advMask, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onTreeItemClickedEdit(QTreeWidgetItem*,int)));
    d->m_itemMenu = new QMenu(0);
}

AdvUserMask::~AdvUserMask()
{
    delete ui;
}

// before calling uiInit, setDevList must be called
void AdvUserMask::uiInit()
{
    Q_D(AdvUserMask);
    ui->tree_advMask->clear();
    QList<QTreeWidgetItem*> topItemList;
    for (int i = 0; i < d->m_devList.count(); i++) {
        SevDevice* dev = d->m_devList.at(i);
        QStringList strList;
        strList<<dev->deviceConfig()->m_modeName;
        QTreeWidgetItem *item = new QTreeWidgetItem(strList);
        item->setText(GT::COL_BOARDTREE_ADDRESS, "-1");
        for (int j = 0; j < dev->axisNum(); j++) {
            QStringList axisStrList;
            axisStrList<<"axis" + QString::number(j + 1);
            QTreeWidgetItem *axisItem = new QTreeWidgetItem(axisStrList);
            axisItem->setText(GT::COL_BOARDTREE_ADDRESS, "-1");
            QTreeWidgetItem *targetItem = GTUtils::findItem(ITEM_NAME_0, dev->axisTreeSource(j, "FLASH"), GT::COL_FLASH_RAM_TREE_NAME);
            modifyItemStructure(axisItem, targetItem, dev);
            item->addChild(axisItem);
        }
        topItemList.append(item);
    }
    ui->tree_advMask->addTopLevelItems(topItemList);
    ui->tree_advMask->installEventFilter(this);
    setItemColor(ui->tree_advMask->invisibleRootItem());

    for (int i = 0; i < ui->tree_advMask->topLevelItemCount(); i++) {
        ui->tree_advMask->topLevelItem(i)->setExpanded(true);
        updateItemData(ui->tree_advMask->topLevelItem(i));
    }
}

QColor AdvUserMask::flashNodeColor()
{
    Q_D(AdvUserMask);
    return d->m_nodeColor;
}

void AdvUserMask::setFlashNodeColor(const QColor &nodeColor)
{
    Q_D(AdvUserMask);
    if (d->m_nodeColor != nodeColor) {
        d->m_nodeColor = nodeColor;
        emit flashNodeColorChanged(d->m_nodeColor);
    }
}

void AdvUserMask::setSevList(const QList<SevDevice *> &list)
{
    Q_D(AdvUserMask);
    d->m_devList = list;
}

bool AdvUserMask::advUserActive()
{
    Q_D(AdvUserMask);
    bool ok;
    for (int i = 0; i < d->m_changedItemList.count(); i++) {
        int devIndex = findDevIndex(d->m_changedItemList.at(i));
        int axisIndex = findAxisIndex(d->m_changedItemList.at(i));
        ok = d->m_devList.at(devIndex)->writeAdvFlash(axisIndex, d->m_changedItemList.at(i));
        if (!ok) {
            respondErrorExecute();
            return false;
        }
        ok = d->m_devList.at(devIndex)->readAdvFlash(axisIndex, d->m_changedItemList.at(i));
        if (!ok) {
            respondErrorExecute();
            return false;
        }
    }
    return true;
}

bool AdvUserMask::readAdv()
{
    return false;
}

bool AdvUserMask::writeAdv()
{
    return false;
}

void AdvUserMask::respondErrorExecute()
{
    QTimer::singleShot(100,this,SLOT(onRespondErrorExe()));
}

void AdvUserMask::contextMenuEvent(QContextMenuEvent *event)
{
    Q_D(AdvUserMask);
    d->m_itemMenu->clear();
    clearLists();
    QPoint point = QCursor::pos();
    QPoint localPos = ui->tree_advMask->viewport()->mapFromGlobal(point);
    QTreeWidgetItem *item = ui->tree_advMask->itemAt(localPos);
    if (item != NULL) {
        if (isDevItem(item)) {
            qDebug()<<"dev item";
            event->accept();
            return;
        } else {
            qDebug()<<"item text"<<item->text(0);
            int devIndex = findDevIndex(item);
            qDebug()<<"dev index"<<devIndex;
            int axisIndex = findAxisIndex(item);
            qDebug()<<"axisIndex"<<axisIndex;
            for (int i = 0; i < ui->tree_advMask->topLevelItem(devIndex)->childCount(); i++) {
                if (i != axisIndex) {
                    QAction *act = new QAction(tr("Copy to Axis%1").arg(i + 1), 0);
                    QList<QVariant> mapVarList;
                    mapVarList.append(devIndex);
                    mapVarList.append(axisIndex);
                    mapVarList.append(i);
                    mapVarList.append(item->text(GT::COL_PAGE_TREE_NAME));
                    act->setData(mapVarList);
                    d->m_actionList.append(act);
                    d->m_itemMenu->addAction(act);
                    connect(act, SIGNAL(triggered()), this, SLOT(onCopySingleAxisTriggered()));
                }
            }
            QAction *copyToAllAxis = new QAction(tr("Copy to all Axis"), 0);
            QList<QVariant> allAxisVarList;
            allAxisVarList.append(devIndex);
            allAxisVarList.append(axisIndex);
            allAxisVarList.append(-1);
            allAxisVarList.append(item->text(GT::COL_PAGE_TREE_NAME));
            copyToAllAxis->setData(allAxisVarList);
            d->m_actionList.append(copyToAllAxis);
            connect(copyToAllAxis, SIGNAL(triggered()), this, SLOT(onCopyAllAxisTriggered()));
            d->m_itemMenu->addAction(copyToAllAxis);
            d->m_itemMenu->addSeparator();


            QAction *clearAlarm = new QAction(tr("Clear alarm"), 0);
            QList<QVariant> clearAlarmVarList;
            clearAlarmVarList.append(devIndex);
            clearAlarmVarList.append(axisIndex);
            clearAlarmVarList.append(-1);
            clearAlarmVarList.append(item->text(GT::COL_PAGE_TREE_NAME));
            clearAlarm->setData(clearAlarmVarList);
            d->m_actionList.append(clearAlarm);
            connect(clearAlarm, SIGNAL(triggered()), this, SLOT(onClearAlarmTriggered()));
            d->m_itemMenu->addAction(clearAlarm);

            QAction *actRefresh = new QAction(tr("Refresh"), 0);
            QList<QVariant> actRefreshVarList;
            actRefreshVarList.append(devIndex);
            actRefreshVarList.append(axisIndex);
            actRefreshVarList.append(-1);
            actRefreshVarList.append(item->text(GT::COL_PAGE_TREE_NAME));
            actRefresh->setData(actRefreshVarList);
            d->m_actionList.append(actRefresh);
            connect(actRefresh, SIGNAL(triggered()), this, SLOT(onRefreshTriggered()));
            d->m_itemMenu->addAction(actRefresh);
        }
        d->m_itemMenu->exec(QCursor::pos());
    }
    event->accept();
}

void AdvUserMask::modifyItemStructure(QTreeWidgetItem *axisItem, QTreeWidgetItem *targetItem, SevDevice *dev)
{
    QTreeWidgetItem* allItem = findItemInTarget(targetItem, STR_MARK_ALL)->clone();
    QTreeWidgetItem* bitItem = findItemInTarget(targetItem, STR_MARK_BIT)->clone();
    axisItem->setText(GT::COL_FLASH_RAM_TREE_VALUE, allItem->text(GT::COL_FLASH_RAM_TREE_VALUE));
    axisItem->setText(GT::COL_FLASH_RAM_TREE_ADDR, allItem->text(GT::COL_FLASH_RAM_TREE_ADDR));
    axisItem->setText(GT::COL_FLASH_RAM_TREE_TYPE, allItem->text(GT::COL_FLASH_RAM_TREE_TYPE));
    QTreeWidget *tree = QtTreeManager::createTreeWidgetFromXmlFile(dev->filePath() + "page/" + INFORMATION_FILENAME);
    QTreeWidgetItem* infoItem = tree->topLevelItem(0);
    //allItem->setText(GT::COL_FLASH_RAM_TREE_NAME, infoItem->text(GT::COL_PAGE_TREE_NAME));
    for (int i = 0; i < bitItem->childCount(); i++) {
        if (bitItem->child(i)->text(GT::COL_FLASH_RAM_TREE_BITWIDTH).compare("1") == 0) {
            QTreeWidgetItem* tempItem = bitItem->child(i)->clone();
            tempItem->setText(GT::COL_FLASH_RAM_TREE_NAME, infoItem->child(i)->text(GT::COL_PAGE_TREE_INTRODUCT));
            axisItem->addChild(tempItem);
        }
    }
    //axisItem->addChild(allItem);
    delete tree;
}

void AdvUserMask::setItemColor(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    if (item->childCount() != 0) {
        for (int i = 0; i < item->columnCount(); i++) {
            item->setTextColor(i, d->m_nodeColor);
        }
        for (int i = 0; i < item->childCount(); i++) {
            setItemColor(item->child(i));
        }
    }
}

bool AdvUserMask::isAxisItem(QTreeWidgetItem *item)
{
    if (item != NULL) {
        QString str = item->text(GT::COL_FLASH_RAM_TREE_NAME);
        if (str.left(4).compare("axis") == 0) {
            return true;
        }
    }
    return false;
}

bool AdvUserMask::isDevItem(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    if (item != NULL) {
        QString str = item->text(GT::COL_FLASH_RAM_TREE_NAME);
        for (int i = 0; i < d->m_devList.count(); i++) {
            if (str.compare(d->m_devList.at(i)->deviceConfig()->m_modeName) == 0) {
                return true;
            }
        }
    }
    return false;
}

void AdvUserMask::calculateItem(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    if (item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("Uint64") == 0 || item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("int64") == 0) {
        quint64 value = BitItemHelper::calculate64Bits(item);
        item->setText(GT::COL_FLASH_RAM_TREE_TYPE, QString::number(value));
    } else if (item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("Uint32") == 0 || item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("int32") == 0){
        quint32 value = BitItemHelper::calculate32Bits(item);
        item->setText(GT::COL_FLASH_RAM_TREE_VALUE, QString::number(value));
    } else {
        quint16 value = BitItemHelper::calculate16Bits(item);
        item->setText(GT::COL_FLASH_RAM_TREE_VALUE, QString::number(value));
    }
    if (!d->m_changedItemList.contains(item)) {
        d->m_changedItemList.append(item);
    }
}

void AdvUserMask::clearLists()
{
    Q_D(AdvUserMask);
    for (int i = 0; i < d->m_actionList.count(); i++) {
        delete d->m_actionList.at(i);
    }
    d->m_actionList.clear();
}

void AdvUserMask::setZero(QTreeWidgetItem* item)
{
    if (item != NULL) {
        item->setText(GT::COL_FLASH_RAM_TREE_VALUE, "0");
        for (int i = 0; i < item->childCount(); i++) {
            setZero(item->child(i));
        }
    }
}

void AdvUserMask::copyItem(QTreeWidgetItem *originItem, QTreeWidgetItem *targetItem)
{
    if (originItem != NULL && targetItem != NULL) {
        QString originText = originItem->text(GT::COL_FLASH_RAM_TREE_VALUE);
        targetItem->setText(GT::COL_FLASH_RAM_TREE_VALUE, originText);
        for (int i = 0; i < originItem->childCount(); i++) {
            copyItem(originItem->child(i), targetItem->child(i));
        }
    }
}

void AdvUserMask::onRespondErrorExe()
{
    QMessageBox::warning(0,tr("Error"),tr("Write warning message error"));
}

void AdvUserMask::onClearAlarmTriggered()
{
    Q_D(AdvUserMask);
    QAction *act = static_cast<QAction *>(sender());
    QList<QVariant> varList = act->data().toList();
    int devIndex = varList.at(0).toInt();
    if (d->m_devList.at(devIndex)->isConnecting()) {
        int axisIndex = varList.at(1).toInt();
        //int copyIndex = varList.at(2).toInt();
        QString itemName = varList.at(3).toString();
        QTreeWidgetItem* originItem = GTUtils::findItemInItem(itemName, ui->tree_advMask->topLevelItem(devIndex)->child(axisIndex), GT::COL_FLASH_RAM_TREE_NAME);
        if (originItem->childCount() == 0) {
            setZero(originItem->parent());
        } else {
            setZero(originItem);
        }
    } else {
        QMessageBox::warning(0,tr("Error"),tr("Not Connected!"));
    }
}

void AdvUserMask::onCopySingleAxisTriggered()
{
    Q_D(AdvUserMask);
    QAction *act = static_cast<QAction *>(sender());
    QList<QVariant> varList = act->data().toList();
    int devIndex = varList.at(0).toInt();
    if (d->m_devList.at(devIndex)->isConnecting()) {
        int axisIndex = varList.at(1).toInt();
        int copyIndex = varList.at(2).toInt();
        QString itemName = varList.at(3).toString();
        QTreeWidgetItem* originItem;
        QTreeWidgetItem* targetItem;
        originItem = GTUtils::findItemInItem(itemName, ui->tree_advMask->topLevelItem(devIndex)->child(axisIndex), GT::COL_FLASH_RAM_TREE_NAME);
        if (isAxisItem(originItem)) {
            targetItem = GTUtils::findItemInItem("axis" + QString::number(copyIndex + 1), ui->tree_advMask->topLevelItem(devIndex), GT::COL_FLASH_RAM_TREE_NAME);
        } else {
            targetItem = GTUtils::findItemInItem(itemName, ui->tree_advMask->topLevelItem(devIndex)->child(copyIndex), GT::COL_FLASH_RAM_TREE_NAME);
        }
        copyItem(originItem, targetItem);
        if (targetItem->childCount() == 0) {
            calculateItem(targetItem->parent());
        } /*else if (isAxisItem(targetItem)) {
            for (int i = 0; i < targetItem->childCount(); i++) {
                calculateItem(targetItem->child(i));
            }
        }*/ else {
            calculateItem(targetItem);
        }
    } else {
        QMessageBox::warning(0,tr("Error"),tr("Not Connected!"));
    }
}

void AdvUserMask::onCopyAllAxisTriggered()
{
    Q_D(AdvUserMask);
    QAction *act = static_cast<QAction *>(sender());
    QList<QVariant> varList = act->data().toList();
    int devIndex = varList.at(0).toInt();
    if (d->m_devList.at(devIndex)->isConnecting()) {
        int axisIndex = varList.at(1).toInt();
        //int copyIndex = varList.at(2).toInt();
        QString itemName = varList.at(3).toString();
        QTreeWidgetItem* originItem = GTUtils::findItemInItem(itemName, ui->tree_advMask->topLevelItem(devIndex)->child(axisIndex), GT::COL_FLASH_RAM_TREE_NAME);
        QTreeWidgetItem* targetItem;
        for (int i = 0; i < ui->tree_advMask->topLevelItem(devIndex)->childCount(); i++) {
            if (i != axisIndex) {
                if (isAxisItem(originItem)) {
                    targetItem = GTUtils::findItemInItem("axis" + QString::number(i + 1), ui->tree_advMask->topLevelItem(devIndex), GT::COL_FLASH_RAM_TREE_NAME);
                } else {
                    targetItem = GTUtils::findItemInItem(itemName, ui->tree_advMask->topLevelItem(devIndex)->child(i), GT::COL_FLASH_RAM_TREE_NAME);
                }
                copyItem(originItem, targetItem);
                if (targetItem->childCount() == 0) {
                    calculateItem(targetItem->parent());
                } /*else if (isAxisItem(targetItem)) {
                    for (int i = 0; i < targetItem->childCount(); i++) {
                        calculateItem(targetItem->child(i));
                    }
                }*/ else {
                    calculateItem(targetItem);
                }
            }
        }
    } else {
        QMessageBox::warning(0,tr("Error"),tr("Not Connected!"));
    }
}

void AdvUserMask::onRefreshTriggered()
{
    Q_D(AdvUserMask);
    QAction *act = static_cast<QAction *>(sender());
    QList<QVariant> varList = act->data().toList();
    int devIndex = varList.at(0).toInt();
    if (d->m_devList.at(devIndex)->isConnecting()) {
        int axisIndex = varList.at(1).toInt();
        //int copyIndex = varList.at(2).toInt();
        QString itemName = varList.at(3).toString();
        QTreeWidgetItem* originItem = GTUtils::findItemInItem(itemName, ui->tree_advMask->topLevelItem(devIndex)->child(axisIndex), GT::COL_FLASH_RAM_TREE_NAME);
        if (originItem->childCount() == 0) {
            updateItemData(originItem->parent());
        } else {
            updateItemData(originItem);
        }
    } else {
        QMessageBox::warning(0,tr("Error"),tr("Not Connected!"));
    }
}

QTreeWidgetItem *AdvUserMask::findItemInTarget(QTreeWidgetItem *targetItem, const QString &str)
{
    for (int i = 0; i < targetItem->childCount(); i++) {
        QTreeWidgetItem *item = targetItem->child(i);
        QStringList list = item->text(GT::COL_FLASH_RAM_TREE_NAME).split(".");
        int listIndex = list.length() - 1;
        if (BitItemHelper::isTargetItem(item, str, listIndex)) {
            return item;
        }
    }
    return NULL;
}

int AdvUserMask::findAxisIndex(QTreeWidgetItem *item)
{
    if (item != NULL) {
        QString itemText = item->text(GT::COL_FLASH_RAM_TREE_NAME);
        if (itemText.left(4).compare("axis") == 0) {
            return itemText.right(1).toInt() - 1;
        } else {
            return findAxisIndex(item->parent());
        }
    }
    return -1;
}

int AdvUserMask::findDevIndex(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    if (item != NULL) {
        QString itemText = item->text(GT::COL_FLASH_RAM_TREE_NAME);
        for (int i = 0; i < d->m_devList.count(); i++) {
            if (itemText.compare(d->m_devList.at(i)->deviceConfig()->m_modeName) == 0) {
                return i;
            }
        }
        return findDevIndex(item->parent());
    }
    return -1;
}

void AdvUserMask::onItemExpanded(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    ui->tree_advMask->resizeColumnToContents(GT::COL_FLASH_RAM_TREE_NAME);
//    int devIndex = findDevIndex(item);
//    if (devIndex != -1 && d->m_devList.at(devIndex)->isConnecting()) {
//        updateItemData(item);
//    } else {
//        qDebug()<<"not connected";
//    }
}

void AdvUserMask::updateItemData(QTreeWidgetItem *item)
{
    //Q_D(UiFLASH);
    if (item->text(GT::COL_FLASH_RAM_TREE_ADDR).compare("-1") != 0) {
        readItem(item);
    }
    for (int i = 0; i < item->childCount(); i++) {
        //if (item->child(i)->isExpanded() || item->child(i)->childCount() == 0) {
            updateItemData(item->child(i));
        //}
    }
}

void AdvUserMask::readItem(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    int devIndex = findDevIndex(item);
    int axisIndex = findAxisIndex(item);
    if (devIndex == -1 || axisIndex == -1) {
        return;
    }
    d->m_devList.at(devIndex)->readAdvFlash(axisIndex, item);
    if (isAxisItem(item)) {
        if (item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("Uint64") == 0 || item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("int64") == 0) {
            quint64 value = item->text(GT::COL_FLASH_RAM_TREE_VALUE).toULongLong();
            BitItemHelper::assign64Bits(item, value);
        } else if (item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("Uint32") == 0 || item->text(GT::COL_FLASH_RAM_TREE_TYPE).compare("int32") == 0) {
            quint32 value = item->text(GT::COL_FLASH_RAM_TREE_VALUE).toULong();
            BitItemHelper::assign32Bits(item, value);
        } else {
            quint16 value = item->text(GT::COL_FLASH_RAM_TREE_VALUE).toUShort();
            BitItemHelper::assign16Bits(item, value);
        }
    }
}

void AdvUserMask::onTreeItemClickedEdit(QTreeWidgetItem *item, int column)
{
    if (column == GT::COL_FLASH_RAM_TREE_VALUE && item->childCount() == 0) {
        if (item->text(GT::COL_FLASH_RAM_TREE_VALUE).compare("1") == 0) {
            item->setText(GT::COL_FLASH_RAM_TREE_VALUE, "0");
            calculateItem(item->parent());
        } else if (item->text(GT::COL_FLASH_RAM_TREE_VALUE).compare("0") == 0) {
            item->setText(GT::COL_FLASH_RAM_TREE_VALUE, "1");
            calculateItem(item->parent());
        }
    }
}
