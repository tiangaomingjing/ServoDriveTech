#ifndef NODELINE_H
#define NODELINE_H
#include "inodeconnection.h"
#include "sdtgraphicsitems_global.h"

class SDTGRAPHICSITEMSSHARED_EXPORT NodeLine : public INodeConnection
{
public:
  explicit NodeLine(NodePort*p1,NodePort*p2,LineDir dir = DIR_UP,bool hasArrow = true,QGraphicsItem * parent = 0);
  ~NodeLine();
  void updatePath() Q_DECL_OVERRIDE;

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
};

#endif // NODELINE_H
