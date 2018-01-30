#include "sdkernel_global.h"
#include <QApplication>

namespace GLO {

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

    QTreeWidgetItem* findItemInItem(QString text, QTreeWidgetItem* tree, int col) {
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

    QString getPath(QTreeWidgetItem *item) {
        QString result = item->text(PWR_COL_INX_VALUE);
        QString fileName = item->text(PWR_COL_INX_VALUE) + ".ui";
        int count = 0;
        QTreeWidgetItem *currentItem = item;
        while (count < 3) {
            currentItem = currentItem->parent();
            result = currentItem->text(PWR_COL_INX_VALUE) + "/" + result;
            count++;
        }
        result = result + "/" + fileName;
        return result;
    }

    QString getFilterPath(QTreeWidgetItem *item) {
        QString result = item->text(PWR_COL_INX_VALUE);
        int count = 0;
        QTreeWidgetItem *currentItem = item;
        while (count < 3) {
            currentItem = currentItem->parent();
            result = currentItem->text(PWR_COL_INX_VALUE) + "/" + result;
            count++;
        }
        result = result + "/filter/";
        return result;
    }
}
