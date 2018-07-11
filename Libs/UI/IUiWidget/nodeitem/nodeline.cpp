#include "nodeline.h"
#include "nodeport.h"

#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>



NodeLine::NodeLine(NodePort *p1, NodePort *p2, LineDir dir,bool hasArrow , QGraphicsItem *parent):
  INodeConnection(p1,p2,dir,hasArrow,parent)
{
  updatePath();
  qDebug()<<"NodeLine construct";
}

NodeLine::~NodeLine()
{

}

void NodeLine::updatePath()
{
//  qDebug()<<"NodeLine updatePath";
//  QPointF pos1(m_port1->scenePos());
//  QPointF pos2(m_port2->scenePos());

  QPointF p1(0+m_port1->rect().width()/2,0+m_port1->rect().height()/2);
  QPointF p2(0+m_port2->rect().width()/2,0+m_port2->rect().height()/2);
  QPointF sp1 = m_port1->mapToScene(p1);
  QPointF sp2 = m_port2->mapToScene(p2);

  QLineF linef(sp1,sp2);

  qreal length = linef.length();
  m_pos1 = linef.pointAt(m_port1->rect().width()/2/length);
  m_pos2 = linef.pointAt((length-m_port2->rect().width()/2)/length);

  QPolygonF myPolygon;
  myPolygon <<m_pos1<<m_pos2;
  setPolygon(myPolygon);
  update();
}

void NodeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    line.setP2(poly.first());

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

