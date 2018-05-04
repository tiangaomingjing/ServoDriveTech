#include "uiram.h"
#include "ui_uiram.h"
#include "iuiwidget_p.h"
#include "sevdevice.h"
#include "gtutils.h"
#include "bititemhelper.h"
#include <QTreeWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

#define STR_MARK_ALL "all"
#define STR_MARK_BIT "bit"

class UiRAMPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiRAM)
public:
  UiRAMPrivate();
  ~UiRAMPrivate();
protected:
  QTreeWidgetItem *m_editedItem;
  int m_editedCol;
  bool m_isEditing;
  QColor m_nodeColor;
  QString m_originText;
};
UiRAMPrivate::UiRAMPrivate()
{

}
UiRAMPrivate::~UiRAMPrivate()
{

}

UiRAM::UiRAM(QWidget *parent):IUiWidget(*(new UiRAMPrivate),parent),ui(new Ui::UiRAM)
{
    Q_D(UiRAM);
  ui->setupUi(this);
  this->setFocus();
  d->m_editedItem = NULL;
  d->m_isEditing = false;
  d->m_nodeColor = Qt::blue;
}

UiRAM::~UiRAM()
{
  delete ui;
}

bool UiRAM::hasConfigFunc()
{
  return false;
}

bool UiRAM::hasSaveFunc()
{
  return false;
}

QColor UiRAM::ramNodeColor()
{
    Q_D(UiRAM);
    return d->m_nodeColor;
}

void UiRAM::setRamNodeColor(const QColor &nodeColor)
{
    Q_D(UiRAM);
    if (d->m_nodeColor != nodeColor) {
        d->m_nodeColor = nodeColor;
        emit ramNodeColorChanged(d->m_nodeColor);
    }
}

void UiRAM::setContextAction()
{

}

void UiRAM::addTreeWidget(QTreeWidget *tree)
{
    Q_D(UiRAM);
    d->m_dataTree = tree;
    d->m_vboxLayout->addWidget(tree);
    d->m_dataTree->installEventFilter(this);
    setItemColor(d->m_dataTree->invisibleRootItem());
    connect(d->m_dataTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onTreeItemClickedEdit(QTreeWidgetItem*,int)));
    connect(d->m_dataTree, SIGNAL(itemSelectionChanged()), this, SLOT(onActionEditFinished()));
    connect(d->m_dataTree, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(onItemExpanded(QTreeWidgetItem*)));
}

bool UiRAM::eventFilter(QObject *obj, QEvent *event)
{
    Q_D(UiRAM);
    if(event->type() == QEvent::KeyPress)
    {
        GTUtils::delayms(100);
        if(obj == d->m_dataTree)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            qDebug()<<keyEvent->key();
            if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
            {
                if (d->m_isEditing) {
                    if (d->m_editedItem != NULL) {
                        d->m_editedItem->setFlags(d->m_editedItem->flags()&(~Qt::ItemIsEditable));
                        if (!isEditedDataValid(d->m_editedItem)) {
                            d->m_editedItem->setText(GT::COL_FR_VALUE, d->m_originText);
                        }
                        if (d->m_device->isConnecting()) {
                            writeItem(d->m_editedItem);
                            d->m_editedItem->setTextColor(d->m_editedCol, Qt::black);
                        } else {
                            QMessageBox::information(this, tr("Warning"), tr("Please connect the device!"));
                        }                        
                        d->m_isEditing = false;
                        d->m_editedItem = NULL;
                    }
                } else {
                    if (d->m_dataTree->selectedItems().length() != 0) {
                        for (int i = 0; i < d->m_dataTree->selectedItems().length(); i++) {
                            QTreeWidgetItem *item = d->m_dataTree->selectedItems().at(i);
                            if (d->m_device->isConnecting()) {
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

QStackedWidget *UiRAM::getUiStackedWidget(void)
{
    return ui->stackedWidget;
}
QVBoxLayout *UiRAM::getVBoxLayout(void)
{
    return ui->verticalLayout_tree;
}
void UiRAM::setDefaultUi()
{
    setCurrentUiIndex(1);
}

void UiRAM::setItemColor(QTreeWidgetItem *item)
{
    Q_D(UiRAM);
    if (item->childCount() != 0) {
        for (int i = 0; i < item->columnCount(); i++) {
            item->setTextColor(i, d->m_nodeColor);
        }
        for (int i = 0; i < item->childCount(); i++) {
            setItemColor(item->child(i));
        }
    }
}

void UiRAM::updateItemData(QTreeWidgetItem *item)
{
    //Q_D(UiRAM);
    if (item->text(GT::COL_FR_ADDRESS).compare("-1") != 0) {
       readItem(item);
    }
    for (int i = 0; i < item->childCount(); i++) {
        if (item->child(i)->isExpanded() || item->child(i)->childCount() == 0) {
            updateItemData(item->child(i));
        }
    }
}

void UiRAM::writeItem(QTreeWidgetItem *item)
{
    Q_D(UiRAM);
    QStringList list = item->text(GT::COL_FR_NAME).split(".");
    int index = list.length() - 1;
    if (BitItemHelper::isTargetItem(item, STR_MARK_BIT, index)) {
        int index = item->parent()->indexOfChild(item);
        QTreeWidgetItem* allItem = item->parent()->child(index - 1);
        if (allItem->text(GT::COL_FR_TYPE).compare("Uint64") == 0 || allItem->text(GT::COL_FR_TYPE).compare("int64") == 0) {
            quint64 value = BitItemHelper::calculate64Bits(item);
            allItem->setText(GT::COL_FR_VALUE, QString::number(value));
        } else if (allItem->text(GT::COL_FR_TYPE).compare("Uint32") == 0 || allItem->text(GT::COL_FR_TYPE).compare("int32") == 0) {
            quint32 value = BitItemHelper::calculate32Bits(item);
            allItem->setText(GT::COL_FR_VALUE, QString::number(value));
        } else {
            quint16 value = BitItemHelper::calculate16Bits(item);
            allItem->setText(GT::COL_FR_VALUE, QString::number(value));
        }
        d->m_device->writeUiRam(uiIndexs().axisInx, allItem);
        d->m_device->readUiRam(uiIndexs().axisInx, allItem);
    } else {
        d->m_device->writeUiRam(uiIndexs().axisInx, item);
        d->m_device->readUiRam(uiIndexs().axisInx, item);
    }
}

void UiRAM::readItem(QTreeWidgetItem *item)
{
    Q_D(UiRAM);
    d->m_device->readUiRam(uiIndexs().axisInx, item);
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

void UiRAM::onTreeItemClickedEdit(QTreeWidgetItem *item, int column)
{
    Q_D(UiRAM);
    if (column == GT::COL_FR_VALUE && item->childCount() == 0) {
        item->setFlags(item->flags()|Qt::ItemIsEditable);
        d->m_originText = item->text(GT::COL_FR_VALUE);
        d->m_dataTree->editItem(item, column);
        d->m_editedItem = item;
        d->m_editedCol = column;
        d->m_isEditing = true;
    } else {
        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
    }
}

void UiRAM::onActionEditFinished()
{
    Q_D(UiRAM);
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

void UiRAM::onItemExpanded(QTreeWidgetItem *item)
{
    Q_D(UiRAM);
    d->m_dataTree->resizeColumnToContents(GT::COL_FR_NAME);
    if (d->m_device->isConnecting()) {
        updateItemData(item);
    } else {
        qDebug()<<"not connected";
    }
}

bool UiRAM::isEditedDataValid(QTreeWidgetItem *item)
{
    Q_D(UiRAM);
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
