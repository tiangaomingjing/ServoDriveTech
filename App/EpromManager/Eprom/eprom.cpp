#include "eprom.h"
#include <QApplication>
#include <QByteArray>
#include <QString>

#define PWR_ID_OFFSET 7
#define CTR_ID_OFFSET 7

EPROM::EPROM(QString filePath, int16 com_type)
{
    m_filePath = filePath;
    m_writeTree = TreeManager::createTreeWidgetFromXmlFile(m_filePath);
    m_type = com_type;
    m_wrongItem = NULL;
    //m_baseAdd = getBaseAddress();
}

EPROM::~EPROM() {

}

bool EPROM::writeFromXmltoEprom(QTreeWidgetItem *writenItem) {
    m_continueWrite = true;
    qDebug()<<"writeFormXmltoEprom: "<<writenItem->text(TREE_NAME);
    if (m_wrongItem != NULL) {
        for (int i = 0; i < m_wrongItem->columnCount(); i++) {
            m_wrongItem->setBackgroundColor(i, Qt::white);
            m_wrongItem->setTextColor(i, Qt::black);
        }
    }
//    while (continueWrite) {
//        writeEEprom(writenItem);
//    }
    bool ok = writeEEprom(writenItem);
    if (m_continueWrite) {
        emit sendWarnMsg(tr("Finish! Please read the data and do the comparison!"));
    }
    return ok;
}

Uint32 EPROM::readID() {
    Uint8 result[4];
    int16 axis = 0;
    Uint16 ofst = PWR_ID_OFFSET + m_baseAdd;
    Uint16 num = 4;
    readEprom(axis, ofst, result, num, m_type, 0xf0);
    Uint32 tempValue = 0;
    for (int i = 0; i < num; i++) {
        tempValue = tempValue + (result[i] << (i * 8));
    }
    return tempValue;
}

bool EPROM::writeEEprom(QTreeWidgetItem *item) {
    bool isOk = false;
    if (m_continueWrite) {
        isOk = writeSingle(item);
        //emit sendScrollItem(item);
        GLO::delayms(5);
        emit updateBarCount();
        if (item->text(TREE_TYPE).compare("Case") == 0) {
            bool ok;
            int index = item->text(TREE_VALUE).toInt(&ok, 10);
            isOk = writeEEprom(item->child(index));
        } else {
            for (int i = 0; i < item->childCount(); i++) {
                isOk = writeEEprom(item->child(i));
                if (!isOk) {
                    break;
                }
            }
        }
    }
    return isOk;
    qApp->processEvents();
}

bool EPROM::writeSingle(QTreeWidgetItem *item) {
    if (item->text(TREE_ADDRESS) != "-1" && item->text(TREE_ADDRESS) != "") {
        emit sendWarnMsg(item->text(TREE_NAME));
        qDebug()<<item->text(0)<<item->text(TREE_ADDRESS);
        bool ok;
        double v;
        Uint8 value[4];
        if (item->text(TREE_ADDRESS).compare("0x0001") == 0) {
            QByteArray temp = item->text(TREE_VALUE).toLatin1();
            value[0] = QString::number(temp.at(0)).toDouble();
            if (temp.size() == 2) {
                value[1] = QString::number(temp.at(1)).toDouble();
            } else {
                value[1] = 0;
            }
            value[2] = 0;
            value[3] = 0;
        } else {
            v = item->text(TREE_VALUE).toDouble() * item->text(TREE_SCALE).toDouble();
            value[0] = v;
            value[1] = int(v)>>8;
            value[2] = int(v)>>16;
            value[3] = int(v)>>24;
        }
        Uint8 result[4];
        int16 axis = 0;
        int count = 0;        
        Uint16 ofst = item->text(TREE_ADDRESS).toUShort(&ok, 16) + m_baseAdd;
        qDebug()<<"ofst"<<ofst;
        if (ofst < 0 || ofst > 1023) {
            ofst = 1023;
        }
        Uint16 num = 0;
        if (item->text(TREE_TYPE) == "Uint8" || item->text(TREE_TYPE) == "int8") {
            //value[0] = v;
            num = 1;
        } else if (item->text(TREE_TYPE) == "Uint16" || item->text(TREE_TYPE) == "int16") {
            num = 2;
            //value[0] = v;
            //value[1] = int(v)>>8;
        } else if (item->text(TREE_TYPE) == "Uint32" || item->text(TREE_TYPE) == "int32") {
            num = 4;
            //value[0] = v;
            //value[1] = int(v)>>8;
            //value[2] = int(v)>>16;
            //value[3] = int(v)>>24;
        }
        int16 ret1;
        int16 ret2;
        ret1 = writeEprom(axis, ofst, value, num, m_type, 0xf0);
        GLO::delayms(5);
        ret2 = readEprom(axis, ofst, result, num, m_type, 0xf0);
        GLO::delayms(5);
        count++;
        while (ret1 != 0 || ret2 != 0 || !writeSuccessful(value, result, num)) {
            ret1 = writeEprom(axis, ofst, value, num, m_type, 0xf0);
            GLO::delayms(5);
            ret2 = readEprom(axis, ofst, result, num, m_type, 0xf0);
            GLO::delayms(5);
            count++;
            if (count > 3) {
                break;
            }
            qDebug()<<"count"<<count;
        }
        if (ret1 != 0 || ret2 != 0 || count > 3) {
            QString warnMsg = tr("Writing failed on ") + item->text(TREE_NAME) + "! ";
            qDebug()<<item->text(TREE_NAME)<<"value "<<value[0]<<value[1]<<value[2]<<value[3];
            qDebug()<<"ret1 = "<<ret1;
            qDebug()<<item->text(TREE_NAME)<<"value "<<result[0]<<result[1]<<result[2]<<result[3];
            qDebug()<<"ret2 = "<<ret2;
            qDebug()<<"axis = "<<axis;
            qDebug()<<"ofst = "<<ofst;
            qDebug()<<"num = "<<num;
            m_continueWrite = false;
            warnMsg = warnMsg + "ret1 = " + ret1 + " ret2 = " + ret2;
            emit sendWarnMsg(warnMsg);
            m_wrongItem = item;
            for (int i = 0; i < m_wrongItem->columnCount(); i++) {
                m_wrongItem->setBackgroundColor(i, Qt::red);
                m_wrongItem->setTextColor(i, Qt::white);
            }
            return false;
        }
    }
    return true;
}

bool EPROM::writeSuccessful(Uint8* value, Uint8* result, Uint16 num) {
    for (int i = 0; i < num; i++) {
        if (value[i] != result[i]) {
            return false;
        }
    }
    return true;
}


bool EPROM::readFromEprom(QTreeWidget *tree) {
    bool ok = true;
    Uint32 id = readID();
    m_readTree = createReadTree(id);
    if (m_readTree == NULL) {
        return ok;
    }
    for (int i = 0; i < m_readTree->topLevelItemCount(); i++) {
        tree->addTopLevelItem(m_readTree->topLevelItem(i)->clone());
    }
//
//    if (readTreeItem == NULL) {
//        return;
//    }
//
    emit changeBarCount(20);
    for (int i = 0; i < m_readTree->topLevelItemCount(); i++) {
        QTreeWidgetItem *readTreeItem = m_readTree->topLevelItem(i);
        QTreeWidgetItem *uiTreeItem = tree->topLevelItem(i);
        ok = readEEpromItem(readTreeItem, uiTreeItem);
        if (!ok) {
            return ok;
        }
    }
    tree->expandAll();
    tree->resizeColumnToContents(0);
    return ok;
}

bool EPROM::readEEpromItem(QTreeWidgetItem* readTreeItem, QTreeWidgetItem* uiTreeItem) {
    bool isOk = readSingle(readTreeItem, uiTreeItem);
    QTreeWidgetItem *newReadItem;
    QTreeWidgetItem *newUiItem;
    bool ok;
    if (readTreeItem->text(TREE_TYPE).compare("Case") == 0) {
        int index = readTreeItem->text(TREE_VALUE).toInt(&ok, 10);
        newReadItem = readTreeItem->child(index);
        newUiItem = uiTreeItem->child(index);
        isOk = readEEpromItem(newReadItem, newUiItem);
    }
    else {
        for (int i = 0; i < readTreeItem->childCount(); i++) {
            newReadItem = readTreeItem->child(i);
            newUiItem = uiTreeItem->child(i);
            isOk = readEEpromItem(newReadItem, newUiItem);
            if (!isOk) {
                break;
            }
        }
    }
    return isOk;
}

bool EPROM::readSingle(QTreeWidgetItem* readTreeItem, QTreeWidgetItem* uiTreeItem) {
    if (readTreeItem->text(TREE_ADDRESS) != "-1" && readTreeItem->text(TREE_ADDRESS) != "") {
        Uint8 result[4];
        int16 axis = 0;
        bool ok;
        Uint16 ofst = readTreeItem->text(TREE_ADDRESS).toInt(&ok, 16) + m_baseAdd;
        Uint16 num = 0;
        if (readTreeItem->text(TREE_TYPE) == "Uint8" || readTreeItem->text(TREE_TYPE) == "int8") {
            num = 1;
        }
        else if (readTreeItem->text(TREE_TYPE) == "Uint16" || readTreeItem->text(TREE_TYPE) == "int16") {
            num = 2;
        }
        else if (readTreeItem->text(TREE_TYPE) == "Uint32" || readTreeItem->text(TREE_TYPE) == "int32") {
            num = 4;
        }
        int16 ret = readEprom(axis, ofst, result, num, m_type, 0xf0);
        if (ret != 0) {
            return false;
        }
        double scale = readTreeItem->text(TREE_SCALE).toDouble(&ok);
        double tempValue = 0;
        for (int j = 0; j < num; j++) {
            tempValue = tempValue + (result[j] << (j * 8));
        }
        if (readTreeItem->text(TREE_ADDRESS).compare("0x0001") == 0) {
            QByteArray tempByte;
            tempByte.append(result[0]);
            if (result[1] != 0) {
                tempByte.append(result[1]);
            }
            QString str = QString::fromLatin1(tempByte);
            qDebug()<<"str"<<str;
            uiTreeItem->setText(TREE_VALUE, str);
        } else {
            if (readTreeItem->text(TREE_TYPE) == "int8") {
                int8 tempValueTwo = tempValue;
                uiTreeItem->setText(TREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
            } else if (readTreeItem->text(TREE_TYPE) == "int16") {
                int16 tempValueTwo = tempValue;
                uiTreeItem->setText(TREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
            } else if (readTreeItem->text(TREE_TYPE) == "int32") {
                int32 tempValueTwo = tempValue;
                uiTreeItem->setText(TREE_VALUE, QString::number(tempValueTwo / scale, 'g', 8));
            } else {
                uiTreeItem->setText(TREE_VALUE, QString::number(tempValue / scale, 'g', 8));
            }
        }
        emit updateBarCount();
        qApp->processEvents();
    }
    return true;
}

void EPROM::compare(QTreeWidget *tree) {
    QTreeWidgetItem *oldNode = tree->topLevelItem(0);
    QTreeWidgetItem *newNode = m_readTree->topLevelItem(1);
    m_exist = false;
    compareNode(oldNode, newNode, tree);
    if (!m_exist) {
        emit sendWarnMsg(tr("Result Correct!"));
    } else {
        emit sendWarnMsg(tr("Error! Please check the data!"));
    }
}

void EPROM::compareNode(QTreeWidgetItem *oldNode, QTreeWidgetItem *newNode, QTreeWidget *tree) {
    emit updateBarCount();
    qApp->processEvents();
    //tree->scrollToItem(oldNode, QAbstractItemView::PositionAtCenter);
    for (int i = 0; i < newNode->childCount(); i++) {
        bool change = false;
        QString newNodeName = newNode->child(i)->text(TREE_NAME);
        for (int j = 0; j < oldNode->childCount(); j++) {
            QString oldNodeName = oldNode->child(j)->text(TREE_NAME);
            if (newNodeName.compare(oldNodeName) == 0) {                
                for (int k = 1; k < oldNode->columnCount(); k++) {
                    if (newNode->child(i)->text(k).toDouble() != oldNode->child(j)->text(k).toDouble()) {
                        change = true;
                        m_exist = true;
                        oldNode->child(j)->setTextColor(k, Qt::white);
                    }
                }
                if (change) {
                    for (int t = 0; t < oldNode->child(j)->columnCount(); t++) {
                        oldNode->child(j)->setBackgroundColor(t, Qt::red);
                        tree->scrollToItem(oldNode, QAbstractItemView::PositionAtCenter);
                    }
                }
                compareNode(oldNode->child(j), newNode->child(i), tree);
                break;
            }
        }
    }
}

QTreeWidget* EPROM::getTree() {
    return m_writeTree;
}
