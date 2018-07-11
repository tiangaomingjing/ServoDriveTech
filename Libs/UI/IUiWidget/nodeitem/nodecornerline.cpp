#include "nodecornerline.h"
#include "nodeport.h"

#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

NodeCornerLine::NodeCornerLine(NodePort *p1, NodePort *p2, LineDir dir, bool hasArrow, QGraphicsItem *parent):
  INodeConnection(p1,p2,dir,hasArrow,parent)

{
  updatePath();
}

void NodeCornerLine::updatePath()
{
  QPointF p1(0+m_port1->rect().width()/2,0+m_port1->rect().height()/2);
  QPointF p2(0+m_port2->rect().width()/2,0+m_port2->rect().height()/2);
  m_pos1 = m_port1->mapToScene(p1);
  m_pos2 = m_port2->mapToScene(p2);
  qreal r1 = m_port1->rect().width()/2;
  qreal r2 = m_port2->rect().width()/2;

  QPointF posMiddle;

  if(m_pos1.y()>m_pos2.y())//从下往上
  {
    if(m_dir == INodeConnection::DIR_UP)
    {
      posMiddle.setX(m_pos1.x());
      posMiddle.setY(m_pos2.y());
    }
    else {
      posMiddle.setX(m_pos2.x());
      posMiddle.setY(m_pos1.y());
    }

  }
  else//从上往下
  {

    if(m_dir == INodeConnection::DIR_UP)
    {
      posMiddle.setX(m_pos2.x());
      posMiddle.setY(m_pos1.y());
    }
    else {
      posMiddle.setX(m_pos1.x());
      posMiddle.setY(m_pos2.y());
    }
  }

  QLineF line1(m_pos1,posMiddle);
  QLineF line2(posMiddle,m_pos2);
  qreal len1 = line1.length();
  qreal len2 = line2.length();
  m_pos1 = line1.pointAt(r1/len1);
  m_pos2 = line2.pointAt((len2 - r2)/len2);

  QPolygonF myPolygon;
  myPolygon <<m_pos1<<posMiddle<<m_pos2;
  setPolygon(myPolygon);
  update();

}

void NodeCornerLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
//  QLineF line;
//  line.setP1(*m_endPoint);
//  if(m_type==ARROW_TYPE_STRAIGHT)
//    line.setP2(*m_startPoint);
//  else
//    line.setP2(*m_cornerPoint);
  if(m_hasArrow)
  {
    QLineF line;
    line.setP1(poly.last());
    line.setP2(poly.at(1));

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

