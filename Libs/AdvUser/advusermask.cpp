#include "advusermask.h"
#include "ui_advusermask.h"
#include "iadvuser_p.h"
#include "gtutils.h"
#include "sdtglobaldef.h"
#include "bititemhelper.h"
#include "deviceconfig.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

#define ITEM_NAME_0 "gSevDrv.sev_obj.cur.pro.prm.alm_mask_flag"
#define STR_MARK_ALL "all"
#define STR_MARK_BIT "bit"

class AdvUserMaskPrivate : public IAdvUserPrivate {
    Q_DECLARE_PUBLIC(AdvUserMask)
public:
    AdvUserMaskPrivate();
    ~AdvUserMaskPrivate();
    QList<SevDevice*> m_devList;
    QTreeWidgetItem *m_editedItem;
    int m_editedCol;
    bool m_isEditing;
    QColor m_nodeColor;
    QString m_originText;
};

AdvUserMaskPrivate::AdvUserMaskPrivate() {

}

AdvUserMaskPrivate::~AdvUserMaskPrivate() {

}

AdvUserMask::AdvUserMask(const QString &usrName, QWidget *parent) :
    IAdvUser(usrName, *new AdvUserMaskPrivate, parent),
    ui(new Ui::AdvUserMask)
{
    Q_D(AdvUserMask);
    ui->setupUi(this);
    this->setFocus();
    d->m_editedItem = NULL;
    d->m_isEditing = false;
    d->m_nodeColor = Qt::blue;
    connect(ui->tree_advMask, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(onItemExpanded(QTreeWidgetItem*)));
    connect(ui->tree_advMask, SIGNAL(itemSelectionChanged()), this, SLOT(onActionEditFinished()));
    connect(ui->tree_advMask, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onTreeItemClickedEdit(QTreeWidgetItem*,int)));
}

AdvUserMask::~AdvUserMask()
{
    delete ui;
}

// before calling uiInit, setDevList must be called
void AdvUserMask::uiInit()
{
    Q_D(AdvUserMask);
    QList<QTreeWidgetItem*> topItemList;
    for (int i = 0; i < d->m_devList.count(); i++) {
        SevDevice* dev = d->m_devList.at(i);
        QStringList strList;
        strList<<dev->deviceConfig()->m_modeName;
        QTreeWidgetItem *item = new QTreeWidgetItem(strList);
        for (int j = 0; j < dev->axisNum(); j++) {
            QStringList axisStrList;
            axisStrList<<"axis" + QString::number(j + 1);
            QTreeWidgetItem *axisItem = new QTreeWidgetItem(axisStrList);
            QTreeWidgetItem *targetItem = GTUtils::findItem(ITEM_NAME_0, dev->axisTreeSource(j, "FLASH"), GT::COL_FR_NAME);
            modifyItemStructure(axisItem, targetItem);
            item->addChild(axisItem);
        }
        topItemList.append(item);
    }
    ui->tree_advMask->addTopLevelItems(topItemList);
    ui->tree_advMask->installEventFilter(this);
    setItemColor(ui->tree_advMask->invisibleRootItem());
}

bool AdvUserMask::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(AdvUserMask);
    if(event->type() == QEvent::KeyPress)
    {
        GTUtils::delayms(100);
        if(obj == ui->tree_advMask)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            //qDebug()<<keyEvent->key();
            if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
            {
                if (d->m_isEditing) {
                    int devIndex = findDevIndex(d->m_editedItem);
                    if (d->m_editedItem != NULL) {
                        d->m_editedItem->setFlags(d->m_editedItem->flags()&(~Qt::ItemIsEditable));
                        if (!isEditedDataValid(d->m_editedItem)) {
                            d->m_editedItem->setText(GT::COL_FR_VALUE, d->m_originText);
                        }
                        if (d->m_devList.at(devIndex)->isConnecting()) {
                            writeItem(d->m_editedItem);
                            d->m_editedItem->setTextColor(d->m_editedCol, Qt::black);
                        } else {
                            QMessageBox::information(this, tr("Warning"), tr("Please connect the device!"));
                        }
                        d->m_isEditing = false;
                        d->m_editedItem = NULL;
                    }
                } else {
                    if (ui->tree_advMask->selectedItems().length() != 0) {
                        for (int i = 0; i < ui->tree_advMask->selectedItems().length(); i++) {
                            QTreeWidgetItem *item = ui->tree_advMask->selectedItems().at(i);
                            int devIndex = findDevIndex(item);
                            if (d->m_devList.at(devIndex)->isConnecting()) {
                                writeItem(item);
                                item->setTextColor(GT::COL_FR_VALUE, Qt::black);
                            } else {
                                QMessageBox::information(this, tr("Warning"), tr("Please connect the device!"));
                            }
                        }
                    }
                }
            return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
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
    return false;
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

}

void AdvUserMask::modifyItemStructure(QTreeWidgetItem *axisItem, QTreeWidgetItem *targetItem)
{
    QTreeWidgetItem* allItem = findItemInTarget(targetItem, STR_MARK_ALL)->clone();
    QTreeWidgetItem* bitItem = findItemInTarget(targetItem, STR_MARK_BIT)->clone();
//    for (int i = 0; i < bitItem->childCount(); i++) {
//        if (bitItem->child(i)->text(GT::COL_FR_BITWIDTH).compare("1") == 0) {
//            allItem->addChild(bitItem->child(i)->clone());
//        }
//    }
//    axisItem->addChild(allItem);
    axisItem->addChild(allItem);
    axisItem->addChild(bitItem);
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

QTreeWidgetItem *AdvUserMask::findItemInTarget(QTreeWidgetItem *targetItem, const QString &str)
{
    for (int i = 0; i < targetItem->childCount(); i++) {
        QTreeWidgetItem *item = targetItem->child(i);
        QStringList list = item->text(GT::COL_FR_NAME).split(".");
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
        QString itemText = item->text(GT::COL_FR_NAME);
        if (itemText.left(4).compare("axis") == 0) {
            return itemText.right(1).toInt();
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
        QString itemText = item->text(GT::COL_FR_NAME);
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
    ui->tree_advMask->resizeColumnToContents(GT::COL_FR_NAME);
    int devIndex = findDevIndex(item);
    if (d->m_devList.at(devIndex)->isConnecting()) {
        updateItemData(item);
    } else {
        qDebug()<<"not connected";
    }
}

void AdvUserMask::updateItemData(QTreeWidgetItem *item)
{
    //Q_D(UiFLASH);
    if (item->text(GT::COL_FR_ADDRESS).compare("-1") != 0) {
        readItem(item);
    }
    for (int i = 0; i < item->childCount(); i++) {
        if (item->child(i)->isExpanded() || item->child(i)->childCount() == 0) {
            updateItemData(item->child(i));
        }
    }
}

void AdvUserMask::writeItem(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    int devIndex = findDevIndex(item);
    int axisIndex = findAxisIndex(item);
    QStringList list = item->text(GT::COL_FR_NAME).split(".");
    int index = list.length() - 1;
    if (BitItemHelper::isTargetItem(item, STR_MARK_BIT, index)) {
        int index = item->parent()->indexOfChild(item);
        QTreeWidgetItem* allItem = item->parent()->child(index - 1);
        if (allItem->text(GT::COL_FR_TYPE).compare("Uint64") == 0 || allItem->text(GT::COL_FR_TYPE).compare("int64") == 0) {
            quint64 value = BitItemHelper::calculate64Bits(item);
            allItem->setText(GT::COL_FR_VALUE, QString::number(value));
        } else if (allItem->text(GT::COL_FR_TYPE).compare("Uint32") == 0 || allItem->text(GT::COL_FR_TYPE).compare("int32") == 0){
            quint32 value = BitItemHelper::calculate32Bits(item);
            allItem->setText(GT::COL_FR_VALUE, QString::number(value));
        } else {
            quint16 value = BitItemHelper::calculate16Bits(item);
            allItem->setText(GT::COL_FR_VALUE, QString::number(value));
        }
        d->m_devList.at(devIndex)->writeUiFlash(axisIndex, allItem);
        d->m_devList.at(devIndex)->readUiFlash(axisIndex, allItem);
    } else {
        d->m_devList.at(devIndex)->writeUiFlash(axisIndex, item);
        d->m_devList.at(devIndex)->readUiFlash(axisIndex, item);
    }
}

void AdvUserMask::readItem(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    int devIndex = findDevIndex(item);
    int axisIndex = findAxisIndex(item);
    d->m_devList.at(devIndex)->readUiFlash(axisIndex, item);
    QStringList list = item->text(GT::COL_FR_NAME).split(".");
    int listIndex = list.length() - 1;
    if (BitItemHelper::isTargetItem(item, STR_MARK_ALL, listIndex)) {
        int index = item->parent()->indexOfChild(item);
        QTreeWidgetItem* bitItem = item->parent()->child(index + 1);
        list = bitItem->text(GT::COL_FR_NAME).split(".");
        listIndex = list.length() - 1;
        if (BitItemHelper::isTargetItem(bitItem, STR_MARK_BIT, listIndex)) {
            if (item->text(GT::COL_FR_TYPE).compare("Uint64") == 0 || item->text(GT::COL_FR_TYPE).compare("int64") == 0) {
                quint64 value = item->text(GT::COL_FR_VALUE).toULongLong();
                BitItemHelper::assign64Bits(bitItem, value);
            } else if (item->text(GT::COL_FR_TYPE).compare("Uint32") == 0 || item->text(GT::COL_FR_TYPE).compare("int32") == 0) {
                quint32 value = item->text(GT::COL_FR_VALUE).toULong();
                BitItemHelper::assign32Bits(bitItem, value);
            } else {
                quint16 value = item->text(GT::COL_FR_VALUE).toUShort();
                BitItemHelper::assign16Bits(bitItem, value);
            }
        }
    }
}

void AdvUserMask::onTreeItemClickedEdit(QTreeWidgetItem *item, int column)
{
    Q_D(AdvUserMask);
    QStringList list = item->text(GT::COL_FR_NAME).split(".");
    int listIndex = list.length() - 1;
    if (column == GT::COL_FR_VALUE && item->childCount() == 0 && BitItemHelper::isTargetItem(item, STR_MARK_ALL, listIndex)) {
        item->setFlags(item->flags()|Qt::ItemIsEditable);
        d->m_originText = item->text(GT::COL_FR_VALUE);
        ui->tree_advMask->editItem(item, column);
        d->m_editedItem = item;
        d->m_editedCol = column;
        d->m_isEditing = true;
    } else if (column == GT::COL_FR_VALUE && item->childCount() == 0) {
        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
        if (item->text(GT::COL_FR_VALUE).compare("1") == 0) {
            item->setText(GT::COL_FR_VALUE, "1");
            writeItem(item);
        } else if (item->text(GT::COL_FR_VALUE).compare("0") == 0) {
            item->setText(GT::COL_FR_VALUE, "0");
            writeItem(item);
        }
    } else {
        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
    }
}

void AdvUserMask::onActionEditFinished()
{
    Q_D(AdvUserMask);
    if (d->m_isEditing) {
        if (d->m_editedItem != NULL) {
            //qDebug()<<"red";
            d->m_editedItem->setFlags(d->m_editedItem->flags()&(~Qt::ItemIsEditable));
            d->m_isEditing = false;
            if (!isEditedDataValid(d->m_editedItem)) {
                d->m_editedItem->setText(GT::COL_FR_VALUE, d->m_originText);
            } else if (d->m_editedItem->text(GT::COL_FR_VALUE).compare(d->m_originText) != 0) {
                d->m_editedItem->setTextColor(d->m_editedCol, Qt::red);
            }
            d->m_editedItem = NULL;
        }
    }
}

bool AdvUserMask::isEditedDataValid(QTreeWidgetItem *item)
{
    Q_D(AdvUserMask);
    QString itemType = item->text(GT::COL_FR_TYPE);
    bool ok;
    QStringList list = item->parent()->text(GT::COL_FR_NAME).split(".");
    int listIndex = list.length() - 1;
    if (BitItemHelper::isTargetItem(item->parent(), STR_MARK_BIT, listIndex)) {
        //qDebug()<<"1";
        quint64 upLimit = pow(2, item->text(GT::COL_FR_BITWIDTH).toInt()) - 1;
        //qDebug()<<"up limit"<<upLimit;
        quint64 downLimit = 0;
        //qDebug()<<"down limit"<<downLimit;
        quint64 value = item->text(GT::COL_FR_VALUE).toULongLong(&ok, 10);
        //qDebug()<<"value"<<value;
        if (value < downLimit || value > upLimit || !ok) {
            //qDebug()<<"false";
            return false;
        }
    } else if (itemType.compare("Uint64") == 0) {
        //qDebug()<<"2";
        quint64 upLimit = 18446744073709551615 - 1;
        quint64 downLimit = 0;
        quint64 value = item->text(GT::COL_FR_VALUE).toULongLong(&ok, 10);
        //qDebug()<<"up limit"<<upLimit;
        //qDebug()<<"down limit"<<downLimit;
        //qDebug()<<"value"<<value;
        if (value < downLimit || value > upLimit || !ok) {
            //qDebug()<<"false";
            return false;
        }
    } else if (itemType.compare("int64") == 0) {
        //qDebug()<<"3";
        qint64 upLimit = 9223372036854775807 - 1;
        qint64 downLimit = -9223372036854775807 + 1;
        qint64 value = item->text(GT::COL_FR_VALUE).toLongLong(&ok, 10);
        //qDebug()<<"up limit"<<upLimit;
        //qDebug()<<"down limit"<<downLimit;
        //qDebug()<<"value"<<value;
        if (value < downLimit || value > upLimit || !ok) {
            //qDebug()<<"false";
            return false;
        }
    } else if (itemType.compare("Uint32") == 0) {
        //qDebug()<<"4";
        quint64 upLimit = 4294967295;
        quint64 downLimit = 0;
        quint64 value = item->text(GT::COL_FR_VALUE).toULongLong(&ok, 10);
        //qDebug()<<"up limit"<<upLimit;
        //qDebug()<<"down limit"<<downLimit;
        //qDebug()<<"value"<<value;
        if (value < downLimit || value > upLimit || !ok) {
            //qDebug()<<"false";
            return false;
        }
    } else if (itemType.compare("int32") == 0) {
        //qDebug()<<"5";
        qint64 upLimit = 2147483647;
        qint64 downLimit = -2147483647;
        qint64 value = item->text(GT::COL_FR_VALUE).toLongLong(&ok, 10);
        //qDebug()<<"up limit"<<upLimit;
        //qDebug()<<"down limit"<<downLimit;
        //qDebug()<<"value"<<value;
        if (value < downLimit || value > upLimit || !ok) {
            //qDebug()<<"false";
            return false;
        }
    } else if (itemType.compare("int16") == 0) {
        //qDebug()<<"6";
        qint64 upLimit = 32767;
        qint64 downLimit = -32767;
        qint64 value = item->text(GT::COL_FR_VALUE).toLongLong(&ok, 10);
        //qDebug()<<"up limit"<<upLimit;
        //qDebug()<<"down limit"<<downLimit;
        //qDebug()<<"value"<<value;
        if (value < downLimit || value > upLimit || !ok) {
            //qDebug()<<"false";
            return false;
        }
    } else {
        //qDebug()<<"7";
        quint64 upLimit = 65535;
        quint64 downLimit = 0;
        quint64 value = item->text(GT::COL_FR_VALUE).toULongLong(&ok, 10);
        //qDebug()<<"up limit"<<upLimit;
        //qDebug()<<"down limit"<<downLimit;
        //qDebug()<<"value"<<value;
        if (value < downLimit || value > upLimit || !ok) {
            //qDebug()<<"false";
            return false;
        }
    }
    return true;
}
