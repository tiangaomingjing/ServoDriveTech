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

