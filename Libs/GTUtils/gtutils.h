#ifndef UTILS_H
#define UTILS_H

#include "gtutils_global.h"
#include <QStringList>

//对应目录下相关文件名
#define SYSCONFIGTREE_NAME            "SysConfigTree.ui"
#define DEVCONFIG_NAME                "DevConfig.ui"
#define FLASH_ALL_PRM_NAME            "FlashPrm_AllAxis.xml"
#define RAM_ALL_PRM_NAME              "RamPrm_AllAxis.xml"
#define POWERBOAD_NAME                "PowerBoard.ui"
#define COMINDEX_NAME                 "ComIndex.ui"
#define CONFIG_SELECTTREE_NAME         "ConfigSelectTree.ui"
#define TARGET_CONFIG_TREE_NAME       "TargetTree.ui"

class QTreeWidgetItem;
class QTreeWidget;
class QTranslator;
class GTUTILSSHARED_EXPORT GTUtils
{

public:
  GTUtils();
  static QString exePath();
  static QString commonPath();
  static QString customPath();
  static QString resPath();
  static QString sysPath();
  static QString databasePath();
  static QString iconPath();
  static QString ubootPath();
  static QString languagePath();
  static void delayms(quint16 ms);
//  static QTreeWidgetItem* findItem(QString text, QTreeWidget* tree, int col);
//  static QTreeWidgetItem* findItemByValue(Uint8* value, Uint16 num, QTreeWidget *tree);
//  static QString getPath(QTreeWidgetItem *item);

  static QList<QTranslator*>setupTranslators(const QString &path);

  static void clearTreeWidgetList(QList<QTreeWidget*> &list);

  static QTreeWidgetItem* findTopLevelItem(QTreeWidgetItem *item);

  static QTreeWidgetItem* findItem(const QString &text, QTreeWidget* tree, int col);
  static QTreeWidgetItem* findItemInItem(const QString &text, QTreeWidgetItem* tree, int col);

private:
  inline static QString sdtPath();
};

#endif // UTILS_H
