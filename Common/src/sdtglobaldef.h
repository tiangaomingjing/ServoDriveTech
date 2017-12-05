#ifndef SDTGLOBALDEF
#define SDTGLOBALDEF
#include <QObject>

#define GT_NAMESPACE_BEGIN namespace GT {
#define GT_NAMESPACE_END }
#define GT_USE_NAMESPACE using namespace GT;

GT_NAMESPACE_BEGIN

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

