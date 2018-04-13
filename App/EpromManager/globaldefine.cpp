#include "globaldefine.h"
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>

namespace GLO {
    void delayms(quint16 ms)
    {
        QTime dieTime = QTime::currentTime().addMSecs(ms);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    QTreeWidgetItem* findItem(QString text, QTreeWidget* tree, int col) {
        QTreeWidgetItemIterator treeIter(tree);
        QTreeWidgetItem *result = NULL;
        while (*treeIter){
            if ((*treeIter)->text(col).compare(text) == 0) {
                result = *treeIter;
                return result;
            }
            ++treeIter;
        }
        return result;
    }

    QTreeWidgetItem* findItemByValue(Uint8* value, Uint16 num, QTreeWidget *tree) {
        int tempValue = 0;
        for (int i = 0; i < num; i++) {
            tempValue = tempValue + (value[i] << (i * 8));
        }
        QTreeWidgetItemIterator treeIter(tree);
        QTreeWidgetItem *result = NULL;
        while (*treeIter){
            if ((*treeIter)->text(TREE_VALUE) == QString::number(tempValue, 10)) {
                result = *treeIter;
                return result;
            }
            ++treeIter;
        }
        return result;
    }

    QString getPath(QTreeWidgetItem *item) {
        //QString result = item->text(TREE_NAME);
        //QString fileName = item->text(TREE_NAME) + ".ui";
        QString result = "";
        int count = 0;
        QTreeWidgetItem *currentItem = item;
        while (count < 3) {
            currentItem = currentItem->parent();
            result = currentItem->text(TREE_NAME) + "/" + result;
            count++;
        }
        //result = result + "/" + fileName;
        return result;
    }
}
