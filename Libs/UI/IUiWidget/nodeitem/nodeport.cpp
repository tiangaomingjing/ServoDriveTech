#include "nodeport.h"
#include "inodeconnection.h"
#include <QPen>
#include <QBrush>

NodePort::NodePort(QGraphicsItem *parent):
  QGraphicsEllipseItem(parent)
{
  setRect(0,0,2,2);
  setFlag(GraphicsItemFlag::ItemIsMovable,true);
  setFlag(GraphicsItemFlag::ItemIsSelectable,true);
  setFlag(GraphicsItemFlag::ItemSendsScenePositionChanges,true);
  setZValue(-1);
  setPen(QPen(Qt::black));
  setBrush(QBrush(Qt::lightGray));
}

NodePort::~NodePort()
{
  foreach(INodeConnection *conn, m_connections)
    delete conn;

  m_connections.clear();
}

bool NodePort::isConnected(const NodePort *other)
{
  foreach(INodeConnection *conn, m_connections)
    if (conn->port1() == other || conn->port2() == other)
      return true;

  return false;
}

QVariant NodePort::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
  if (change == ItemScenePositionHasChanged)
  {
    foreach(INodeConnection *conn, m_connections)
    {
      conn->updatePath();
//      qDebug()<<conn->pos();
    }
  }
  return value;
}

NodeBlock *NodePort::nodeBlock() const
{
  return m_nodeBlock;
}

void NodePort::setNodeBlock(NodeBlock *nodeBlock)
{
  m_nodeBlock = nodeBlock;
}

void NodePort::addNodeConnection(INodeConnection *connection)
{
  m_connections.append(connection);
}

void NodePort::removeNodeConnection(INodeConnection *connection)
{
  m_connections.removeOne(connection);
}

