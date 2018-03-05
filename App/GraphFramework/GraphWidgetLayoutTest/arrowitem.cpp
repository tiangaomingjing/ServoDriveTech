#include "arrowitem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QPolygonF>
#include <QDebug>
#include <math.h>
const qreal Pi = 3.14;

enum ArrowDir{
  ARROW_DIR_LEFT_UP,
  ARROW_DIR_LEFT_DOWN,
  ARROW_DIR_RIGHT_UP,
  ARROW_DIR_RIGHT_DOWN
};

ArrowItem::ArrowItem(QPointF *startPoint, QPointF *endPoint, ArrowType type, const QString &text, bool hasArrow, QGraphicsItem *parent):
  QGraphicsPolygonItem(parent),
  m_startPoint(startPoint),
  m_endPoint(endPoint),
  m_cornerPoint(new QPointF(0,0)),
  m_type(type),
  m_color(Qt::blue),
  m_text(text),
  m_hasArrow(hasArrow)
{
  QPolygonF myPolygon = calculatePolygon();
  setPolygon(myPolygon);
//  setFlag(QGraphicsItem::ItemIsMovable, true);
//  setFlag(QGraphicsItem::ItemIsSelectable, true);
//  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

ArrowItem::~ArrowItem()
{
  delete m_cornerPoint;
}

QPolygonF ArrowItem::calculatePolygon()
{
  QPolygonF myPolygon;
  if(m_type==ARROW_TYPE_STRAIGHT)
  {
    myPolygon<<*m_startPoint<<*m_endPoint;
  }
  else
  {
    //判断是左右?
    ArrowDir dir = ARROW_DIR_LEFT_UP;
    if(m_startPoint->x()>m_endPoint->x())//left
    {
      if(m_startPoint->y()>m_endPoint->y())//up
      {
        dir=ARROW_DIR_LEFT_UP;
      }
      else
      {
        dir=ARROW_DIR_LEFT_DOWN;
      }
    }
    else//right
    {
      if(m_startPoint->y()>m_endPoint->y())//up
      {
        dir=ARROW_DIR_RIGHT_UP;
      }
      else
      {
        dir=ARROW_DIR_RIGHT_DOWN;
      }
    }
    //求拐点坐标
    switch (dir) {
    case ARROW_DIR_LEFT_UP:
      m_cornerPoint->setX(m_endPoint->x());
      m_cornerPoint->setY(m_startPoint->y());
      break;
    case ARROW_DIR_RIGHT_UP:
      m_cornerPoint->setX(m_startPoint->x());
      m_cornerPoint->setY(m_endPoint->y());
      break;
    case ARROW_DIR_RIGHT_DOWN:
      m_cornerPoint->setX(m_endPoint->x());
      m_cornerPoint->setY(m_startPoint->y());
      break;
    default://左下
      m_cornerPoint->setX(m_endPoint->x());
      m_cornerPoint->setY(m_startPoint->y());
      break;
    }
    myPolygon<<*m_startPoint<<*m_cornerPoint<<*m_endPoint;
  }

  return myPolygon;
}

void ArrowItem::setText(const QString &text)
{
  m_text = text;
}

void ArrowItem::updatePosition()
{
  QPolygonF myPolygon;
  myPolygon=calculatePolygon();
  setPolygon(myPolygon);
  update();
  qDebug()<<"myPolygon"<<myPolygon;
}

void ArrowItem::setColor(const QColor &color)
{
  if(m_color!=color)
  {
    m_color=color;

    update();
  }
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    if(m_type==ARROW_TYPE_STRAIGHT)
      line.setP2(poly.first());
    else
      line.setP2(poly.at(1));

    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line.p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                    cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                    cos(angle + Pi - Pi / 3) * arrowSize);

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

