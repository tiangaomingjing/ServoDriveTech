#include "nodeswitch.h"
#include "nodeport.h"

#include <QPen>
#include <QBrush>
#include <QPainter>

#define PORT_RADIUS 10

NodeSwitch::NodeSwitch(QGraphicsItem *parent):
  QGraphicsPathItem(parent),
  m_penColor(Qt::gray),
  m_brushColor(Qt::lightGray),
  m_brushSelectedColor(Qt::lightGray)
{
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  m_leftPort = new NodePort(this);
  m_topPort = new NodePort(this);
  m_bottomPort = new NodePort(this);

  m_leftPort->setRect(0,0,PORT_RADIUS,PORT_RADIUS);
  m_topPort->setRect(0,0,PORT_RADIUS,PORT_RADIUS);
  m_bottomPort->setRect(0,0,PORT_RADIUS,PORT_RADIUS);

  setPen(QPen(m_penColor));
  setBrush(m_brushColor);

  QPainterPath p;
  p.addRoundedRect(0, 0, 60, 40, 5, 5);
  setPath(p);

  qreal w = boundingRect().width();
  qreal h = boundingRect().height();
  qreal d = m_leftPort->rect().width();
//  m_leftPort->setPos(0+d,h/2.0+d/2.0);
//  m_topPort->setPos(w-2*d,0+d);
//  m_bottomPort->setPos(w-2*d,h-d);
  m_leftPort->setPos(0+d,h/2.0-d/2.0);
  m_topPort->setPos(w-2*d,0+d/2.0);
  m_bottomPort->setPos(w-2*d,h-1.5*d);
}

NodeSwitch::~NodeSwitch()
{

}

NodePort *NodeSwitch::leftPort() const
{
  return m_leftPort;
}

NodePort *NodeSwitch::topPort() const
{
  return m_topPort;
}

NodePort *NodeSwitch::bottomPort() const
{
  return m_bottomPort;
}

void NodeSwitch::setPortColor(const QColor &clr)
{
  QPen mPen(clr);
  m_leftPort->setPen(mPen);
  m_topPort->setPen(mPen);
  m_bottomPort->setPen(mPen);
}

void NodeSwitch::setPortBrushColor(const QColor &clr)
{
  QBrush b(clr);
  m_leftPort->setBrush(b);
  m_topPort->setBrush(b);
  m_bottomPort->setBrush(b);
}

void NodeSwitch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)

  QPen mPen(m_penColor);
  mPen.setWidth(2);
  if (isSelected()) {
    painter->setPen(mPen);
    painter->setBrush(m_brushSelectedColor);
  } else {
    painter->setPen(mPen);
    painter->setBrush(m_brushColor);
  }
  painter->drawPath(path());


  QLineF  line;
  QPointF offsetPoint(m_leftPort->rect().width()/2,m_leftPort->rect().width()/2);
  line.setP1(m_leftPort->pos()+offsetPoint);
  if(m_isOn)
  {
    line.setP2(m_topPort->pos()+offsetPoint);
  }
  else
    line.setP2(m_bottomPort->pos()+offsetPoint);

  painter->drawLine(line);
}

void NodeSwitch::setPenColor(const QColor &penColor)
{
  m_penColor = penColor;
}

void NodeSwitch::setBrushColor(const QColor &brushColor)
{
  m_brushColor = brushColor;
}

void NodeSwitch::setBrushSelectedColor(const QColor &brushSelectedColor)
{
  m_brushSelectedColor = brushSelectedColor;
}

bool NodeSwitch::isOn() const
{
  return m_isOn;
}

void NodeSwitch::setIsOn(bool isOn)
{
  m_isOn = isOn;
  update(boundingRect());
}

void NodeSwitch::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  Q_UNUSED(event);
  m_isOn =!m_isOn;
  update(boundingRect());
  emit clicked(m_isOn);
}

