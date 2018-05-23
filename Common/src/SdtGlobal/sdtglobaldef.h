#ifndef SDTGLOBALDEF
#define SDTGLOBALDEF
#include <QObject>
#include <QMutexLocker>
#include <QMutex>

#define GT_NAMESPACE_BEGIN namespace GT {
#define GT_NAMESPACE_END }
#define GT_USE_NAMESPACE using namespace GT;

GT_NAMESPACE_BEGIN
typedef enum{
  COL_TARGET_CONFIG_NAME,
  COL_TARGET_CONFIG_PRM,
  COL_TARGET_CONFIG_CLASS,
  COL_TARGET_CONFIG_XML,
  COL_TARGET_CONFIG_INDEX,
  COL_TARGET_CONFIG_FILESRCTYPE,
  COL_TARGET_CONFIG_ISPLOT
}TargetConfigColumn;
typedef enum{
  COL_PAGE_TREE_NAME,
  COL_PAGE_TREE_VALUE,
  COL_PAGE_TREE_TYPE,
  COL_PAGE_TREE_UNIT,
  COL_PAGE_TREE_DLIMIT,
  COL_PAGE_TREE_ULIMIT,
  COL_PAGE_TREE_INTRODUCT,
  COL_PAGE_TREE_ADDR,
  COL_PAGE_TREE_SCALE
}PageTreeColumn;
typedef enum{
  ROW_TARGET_CONFIG_AXIS,
  ROW_TARGET_CONFIG_GLOBAL
}TargetConfigRow;

typedef enum {
    COL_CONFIG_NAME = 0,
    COL_CONFIG_PARAMETER = 1,
    COL_CONFIG_ID = 2,
    COL_CONFIG_PRMEX = 3
} ColConfigTree;

typedef enum {
    COL_BOARDTREE_NAME = 0,
    COL_BOARDTREE_VALUE = 1,
    COL_BOARDTREE_UNIT = 2,
    COL_BOARDTREE_SCALE = 3,
    COL_BOARDTREE_DESCRIP = 4,
    COL_BOARDTREE_TYPE = 5,
    COL_BOARDTREE_ADDRESS = 6,
    COL_BOARDTREE_CTRNAME = 7,
    COL_BOARDTREE_CTRMAX = 8,
    COL_BOARDTREE_CTRMIN = 9,
    COL_BOARDTREE_UNIQUENAME = 10
} ColBoardTree;

typedef enum {
    COL_INDEX_NAME = 0,
    COL_INDEX_VALUE = 1
} ColIndexTree;

typedef enum
{
  COL_IDMAP_ID = 0,
  COL_IDMAP_TYPE = 1,
  COL_IDMAP_MODE = 2,
  COL_IDMAP_NICKNAME = 3,
  COL_IDMAP_AXISNUM = 4
} ColIdMap;


typedef enum{
  COL_FLASH_RAM_TREE_NAME,
  COL_FLASH_RAM_TREE_VALUE,
  COL_FLASH_RAM_TREE_TYPE,
  COL_FLASH_RAM_TREE_ADDR,
  COL_FLASH_RAM_TREE_ISBIT,
  COL_FLASH_RAM_TREE_BITSTART,
  COL_FLASH_RAM_TREE_BITWIDTH
}FlashRamColumn;

typedef enum {
    COL_FLASH_ALLAXIS_NAME,
    COL_FLASH_ALLAXIS_VALUE,
    COL_FLASH_ALLAXIS_TYPE,
    COL_FLASH_ALLAXIS_ADDR,
}FlashAllAxisColumn;

typedef enum {
    COL_PRM_PRTY_NAME,
    COL_PRM_PRTY_TYPE,
    COL_PRM_PRTY_MAX,
    COL_PRM_PRTY_MIN,
}PrmPrtyColumn;

typedef enum {
  SEV_CTL_SRC_PC,
  SEV_CTL_SRC_GLINK2
}SevControlSrc;

template <typename T>
static void deepClearList(QList<T*>&list)
{
  T* item;
  for(int i=0;i<list.count();i++)
  {
    item=list.at(i);
    delete item;
  }
  list.clear();
}

template <typename T>
static void deletePtrObject(T*obj)
{
  if(obj!=NULL)
  {
    delete obj;
    obj=NULL;
  }
}

GT_NAMESPACE_END
#endif // SDTGLOBALDEF

