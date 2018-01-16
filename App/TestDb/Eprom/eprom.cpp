#include "eprom.h"
#include <QApplication>

EPROM::EPROM(QString filePath, int16 com_type)
{
    m_filePath = filePath;
    m_writeTree = TreeManager::createTreeWidgetFromXmlFile(m_filePath);
    m_type = com_type;
    m_wrongItem = NULL;
    QTreeWidgetItem *xmlBaseAdd;
    bool ok;
    xmlBaseAdd = GLO::findItem("xmlBaseAddress", m_writeTree, TREE_NAME);
    baseAdd = xmlBaseAdd->text(TREE_VALUE).toInt(&ok, 10);
    delete xmlBaseAdd;
    //qDebug()<<baseAdd;
}

EPROM::~EPROM() {

}

void EPROM::writeFromXmltoEprom(QTreeWidgetItem *writenItem) {
    continueWrite = true;
    qDebug()<<"writeFormXmltoEprom: "<<writenItem->text(TREE_NAME);
    if (m_wrongItem != NULL) {
        for (int i = 0; i < m_wrongItem->columnCount(); i++) {
            m_wrongItem->setBackgroundColor(i, Qt::white);
            m_wrongItem->setTextColor(i, Qt::black);
        }
    }
    writeEEprom(writenItem);
    if (continueWrite) {
        emit sendWarnMsg(tr("Finish!"));
    }
}

Uint32 EPROM::readID() {
    Uint8 result[4];
    int16 axis = 0;
    Uint16 ofst = 1 + baseAdd;
    qDebug()<<"ofst"<<ofst;
    Uint16 num = 4;
    readEprom(axis, ofst, result, num, m_type, 0xf0);
    Uint32 tempValue = 0;
    for (int i = 0; i < num; i++) {
        tempValue = tempValue + (result[i] << (i * 8));
    }
    return tempValue;
}

void EPROM::writeEEprom(QTreeWidgetItem *item) {
    if (continueWrite) {
        writeSingle(item);
        emit sendScrollItem(item);
        GLO::delayms(10);
        emit updateBarCount();
        if (item->text(TREE_TYPE).compare("Case") == 0) {
            bool ok;
            int index = item->text(TREE_VALUE).toInt(&ok, 10);
            writeEEprom(item->child(index));
        } else {
            for (int i = 0; i < item->childCount(); i++) {
                writeEEprom(item->child(i));
            }
        }
    }
    qApp->processEvents();
}

void EPROM::writeSingle(QTreeWidgetItem *item) {
    if (item->text(TREE_ADDRESS) != "-1" && item->text(TREE_ADDRESS) != "") {
        qDebug()<<item->text(0)<<item->text(TREE_ADDRESS);
        bool ok;
        double v;
        v = item->text(TREE_VALUE).toDouble() * item->text(TREE_SCALE).toDouble();
        Uint8 value[4];
        Uint8 result[4];
        int16 axis = 0;
        int count = 0;
        value[0] = v;
        value[1] = int(v)>>8;
        value[2] = int(v)>>16;
        value[3] = int(v)>>24;
        Uint16 ofst = item->text(TREE_ADDRESS).toUShort(&ok, 16) + baseAdd;
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
        GLO::delayms(10);
        ret2 = readEprom(axis, ofst, result, num, m_type, 0xf0);
        GLO::delayms(10);
        count++;
        while (ret1 != 0 || ret2 != 0 || !writeSuccessful(value, result, num)) {
            ret1 = writeEprom(axis, ofst, value, num, m_type, 0xf0);
            GLO::delayms(10);
            ret2 = readEprom(axis, ofst, result, num, m_type, 0xf0);
            GLO::delayms(10);
            count++;
            if (count > 3) {
                break;
            }
            qDebug()<<"count"<<count;
        }
        if (ret1 != 0 || ret2 != 0 || count > 3) {
            QString warnMsg = tr("Writing failed on ") + item->text(TREE_NAME) + "!";
            qDebug()<<item->text(TREE_NAME)<<"value "<<value[0]<<value[1]<<value[2]<<value[3];
            qDebug()<<"ret1 = "<<ret1;
            qDebug()<<item->text(TREE_NAME)<<"value "<<result[0]<<result[1]<<result[2]<<result[3];
            qDebug()<<"ret2 = "<<ret2;
            qDebug()<<"axis = "<<axis;
            qDebug()<<"ofst = "<<ofst;
            qDebug()<<"num = "<<num;
            continueWrite = false;
            emit sendWarnMsg(warnMsg);
            m_wrongItem = item;
            for (int i = 0; i < m_wrongItem->columnCount(); i++) {
                m_wrongItem->setBackgroundColor(i, Qt::red);
                m_wrongItem->setTextColor(i, Qt::white);
            }
            return;
        }
    }
}

bool EPROM::writeSuccessful(Uint8* value, Uint8* result, Uint16 num) {
    for (int i = 0; i < num; i++) {
        if (value[i] != result[i]) {
            return false;
        }
    }
    return true;
}


void EPROM::readFromEprom(QTreeWidget *tree) {
    Uint32 id = readID();
    m_readTree = createReadTree(id);
    if (m_readTree == NULL) {
        return;
    }
    QString idStr = QString::number(id, 10);
    tree->addTopLevelItem(m_readTree->topLevelItem(1)->clone());
    QTreeWidgetItem *readTreeItem = GLO::findItem(idStr, m_readTree, TREE_VALUE);
    if (readTreeItem == NULL) {
        return;
    }
    QTreeWidgetItem *uiTreeItem = GLO::findItem(idStr, tree, TREE_VALUE);
    emit changeBarCount(20);
    readEEpromItem(readTreeItem, uiTreeItem);
    tree->expandAll();
    tree->resizeColumnToContents(0);
}

void EPROM::readEEpromItem(QTreeWidgetItem* readTreeItem, QTreeWidgetItem* uiTreeItem) {
    readSingle(readTreeItem, uiTreeItem);
    QTreeWidgetItem *newReadItem;
    QTreeWidgetItem *newUiItem;
    bool ok;
    if (readTreeItem->text(TREE_TYPE).compare("Case") == 0) {
        int index = readTreeItem->text(TREE_VALUE).toInt(&ok, 10);
        newReadItem = readTreeItem->child(index);
        newUiItem = uiTreeItem->child(index);
        readEEpromItem(newReadItem, newUiItem);
    }
    else {
        for (int i = 0; i < readTreeItem->childCount(); i++) {
            newReadItem = readTreeItem->child(i);
            newUiItem = uiTreeItem->child(i);
            readEEpromItem(newReadItem, newUiItem);
        }
    }
}

void EPROM::readSingle(QTreeWidgetItem* readTreeItem, QTreeWidgetItem* uiTreeItem) {
    if (readTreeItem->text(TREE_ADDRESS) != "-1" && readTreeItem->text(TREE_ADDRESS) != "") {
        Uint8 result[4];
        int16 axis = 0;
        bool ok;
        Uint16 ofst = readTreeItem->text(TREE_ADDRESS).toInt(&ok, 16) + baseAdd;
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
        readEprom(axis, ofst, result, num, m_type, 0xf0);
        double scale = readTreeItem->text(TREE_SCALE).toDouble(&ok);
        double tempValue = 0;
        for (int j = 0; j < num; j++) {
            tempValue = tempValue + (result[j] << (j * 8));
        }
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
        emit updateBarCount();
        qApp->processEvents();
    }
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
    tree->scrollToItem(oldNode, QAbstractItemView::PositionAtCenter);
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
