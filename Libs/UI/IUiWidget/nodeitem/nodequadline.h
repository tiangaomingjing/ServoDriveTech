#ifndef NODEQUADLINE_H
#define NODEQUADLINE_H
#include "inodeconnection.h"
#include "sdtgraphicsitems_global.h"

class SDTGRAPHICSITEMSSHARED_EXPORT NodeQuadLine : public INodeConnection
{
public:
  explicit NodeQuadLine(NodePort*p1,NodePort*p2,LineDir dir = DIR_UP,bool hasArrow = true ,QGraphicsItem * parent = 0);
  void updatePath() Q_DECL_OVERRIDE;

  qreal qualHeight() const;
  void setQualHeight(const qreal &qualHeight);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
  qreal m_qualHeight;
};

#endif // NODEQUADLINE_H
