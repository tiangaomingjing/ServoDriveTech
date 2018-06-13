#ifndef NODEITEMGLOBALDEF
#define NODEITEMGLOBALDEF

#include <QGraphicsPathItem>

namespace NodeItem
{
  typedef enum {
  NODE_PORT = QGraphicsItem::UserType + 1,
  NODE_BLOCK ,
  NODE_LINE
}NodeItemType;
}

#endif // NODEITEMGLOBALDEF

