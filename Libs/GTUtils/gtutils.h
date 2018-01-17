#ifndef UTILS_H
#define UTILS_H

#include "gtutils_global.h"

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

  static void clearTreeWidgetList(QList<QTreeWidget*> &list);

private:
  inline static QString sdtPath();
};


#endif // UTILS_H
