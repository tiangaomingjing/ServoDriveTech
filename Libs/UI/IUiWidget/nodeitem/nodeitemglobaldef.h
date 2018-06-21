#ifndef NODEITEMGLOBALDEF
#define NODEITEMGLOBALDEF

#include <QGraphicsItem>
#include <QDebug>

namespace NodeItem
{
  typedef enum {
  NODE_PORT = QGraphicsItem::UserType + 1,
  NODE_BLOCK ,
  NODE_CONNECT
}NodeItemType;
  const qreal Pi = 3.14;
}

#endif // NODEITEMGLOBALDEF

