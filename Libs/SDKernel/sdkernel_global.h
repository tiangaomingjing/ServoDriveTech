#ifndef SDKERNEL_GLOBAL_H
#define SDKERNEL_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QTreeWidget>

#if defined(SDKERNEL_LIBRARY)
#  define SDKERNELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SDKERNELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SDKERNEL_GLOBAL_H
enum PwrColumnInx{
  PWR_COL_INX_NAME,
  PWR_COL_INX_VALUE,
  PWR_COL_INX_UNIT,
  PWR_COL_INX_SCALE,
  PWR_COL_INX_DESCRIPTION,
  PWR_COL_INX_TYPE,
  PWR_COL_INX_ADDR,
  PWR_COL_INX_CTLNAME,
  PWR_COL_INX_CTLMAX,
  PWR_COL_INX_CTLMIN,
  PWR_COL_INX_UNIQUENAME
};

namespace GLO {
    QTreeWidgetItem* findItem(QString text, QTreeWidget* tree, int col);
    QTreeWidgetItem* findItemInItem(QString text, QTreeWidgetItem* tree, int col);
    QString getPath(QTreeWidgetItem *item);
    QString getFilterPath(QTreeWidgetItem *item);
}
