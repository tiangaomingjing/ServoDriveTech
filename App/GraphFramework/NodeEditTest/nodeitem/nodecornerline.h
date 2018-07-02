#ifndef NODECORNERLINE_H
#define NODECORNERLINE_H
#include "inodeconnection.h"

class NodeCornerLine : public INodeConnection
{
public:
  explicit NodeCornerLine(NodePort*p1,NodePort*p2,LineDir dir = DIR_UP,bool hasArrow = true ,QGraphicsItem * parent = 0);
  void updatePath() Q_DECL_OVERRIDE;

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
};

#endif // NODECORNERLINE_H
