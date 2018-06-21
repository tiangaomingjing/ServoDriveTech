#ifndef NODEPORT_H
#define NODEPORT_H

#include <QGraphicsEllipseItem>
#include "nodeitemglobaldef.h"
#include "sdtgraphicsitems_global.h"

class INodeConnection;
class NodeBlock;

class SDTGRAPHICSITEMSSHARED_EXPORT NodePort : public QGraphicsEllipseItem
{
public:
  enum { Type = NodeItem::NODE_PORT };
  explicit NodePort(QGraphicsItem *parent = 0);
  ~NodePort();
  int type() const { return Type; }

  bool isConnected(const NodePort *other);

  NodeBlock *nodeBlock() const;
  void setNodeBlock(NodeBlock *nodeBlock);

  void addNodeConnection(INodeConnection* connection);
  void removeNodeConnection(INodeConnection* connection);

protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
  NodeBlock *m_nodeBlock;
  QVector<INodeConnection*> m_connections;
};

#endif // NODEPORT_H
