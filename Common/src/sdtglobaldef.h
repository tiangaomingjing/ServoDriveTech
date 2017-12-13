#ifndef SDTGLOBALDEF
#define SDTGLOBALDEF
#include <QObject>

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
  COL_TARGET_CONFIG_FILESRCTYPE
}TargetConfigColumn;
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

GT_NAMESPACE_END
#endif // SDTGLOBALDEF

