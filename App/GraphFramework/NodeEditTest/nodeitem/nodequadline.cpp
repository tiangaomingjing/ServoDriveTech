#include "nodequadline.h"
#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#define MIN_QUAD_HEIGHT 20

NodeQuadLine::NodeQuadLine(NodePort *p1, NodePort *p2, LineDir dir, bool hasArrow, QGraphicsItem *parent):
  INodeConnection(p1,p2,dir,hasArrow,parent),
  m_qualHeight(MIN_QUAD_HEIGHT)
{
  updatePath();
}

void NodeQuadLine::updatePath()
{
  updatePos12();

  QPointF posM1,posM2;
  if(m_dir == INodeConnection::DIR_UP)
  {
    qreal h = 0;
    if(m_pos1.y()>m_pos2.y())
    {
      h = m_pos2.y() - m_qualHeight;
    }
    else
    {
      h = m_pos1.y() - m_qualHeight;
    }
    posM1.setX(m_pos1.x());
    posM1.setY(h);
    posM2.setX(m_pos2.x());
    posM2.setY(h);

  }
  else
  {
    qreal h = 0;
    if(m_pos1.y()>m_pos2.y())
    {
      h = m_pos1.y() + m_qualHeight;
    }
    else
    {
      h = m_pos2.y() + m_qualHeight;
    }
    posM1.setX(m_pos1.x());
    posM1.setY(h);
    posM2.setX(m_pos2.x());
    posM2.setY(h);
  }

  QPolygonF myPolygon;
  myPolygon <<m_pos1<<posM1<<posM2<<m_pos2;
  setPolygon(myPolygon);
  update();
}

void NodeQuadLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

  qreal arrowSize = 10;
  QPolygonF poly=polygon();
  QPen myPen=pen();
  myPen.setWidth(2);
  myPen.setColor(m_color);
  painter->setPen(myPen);
  painter->setBrush(m_color);
//  painter->drawPolygon(poly);
  painter->drawPolyline(poly);

  //draw arrow
  if(m_hasArrow)
  {
    QLineF line;
    line.setP1(poly.last());
    line.setP2(poly.at(2));

    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = (NodeItem::Pi * 2) - angle;

    QPointF arrowP1 = line.p1() + QPointF(sin(angle + NodeItem::Pi / 3) * arrowSize,
                                    cos(angle + NodeItem::Pi / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + NodeItem::Pi - NodeItem::Pi / 3) * arrowSize,
                                    cos(angle + NodeItem::Pi - NodeItem::Pi / 3) * arrowSize);

    QPolygonF arrowPolygon;
    arrowPolygon << line.p1() << arrowP1 << arrowP2;
    painter->drawPolygon(arrowPolygon);

    if(!m_text.isEmpty())
    {
      QLineF rVtr=line.unitVector();
      QLineF nVtr=line.normalVector().unitVector();
  //      qDebug()<<"==============================="<<m_text;
  //      qDebug()<<"line"<<line;
  //      qDebug()<<"rVtr"<<rVtr<<"dx"<<rVtr.dx()<<"dy"<<rVtr.dy();
  //      qDebug()<<"nVtr"<<nVtr<<"dx"<<nVtr.dx()<<"dy"<<nVtr.dy();
      arrowP2+=QPointF(10*nVtr.dx(),10*rVtr.dy());
  //      qDebug()<<"draw point"<<arrowP2;
      painter->drawText(arrowP2,m_text);
    }
  }
}

qreal NodeQuadLine::qualHeight() const
{
  return m_qualHeight;
}

void NodeQuadLine::setQualHeight(const qreal &qualHeight)
{
  m_qualHeight = qualHeight;
}

