#include "sumitem.h"
#include <QPainter>

SumItem::SumItem(QGraphicsItem *parent):QGraphicsItem(parent)
{

}

SumItem::~SumItem()
{

}

QRectF SumItem::boundingRect() const
{
  qreal adjust=0.5;
  return QRectF(0-adjust,0-adjust,50+adjust,50+adjust);
}

void SumItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setRenderHint(QPainter::Antialiasing);
  painter->drawEllipse(0,0,50,50);
  painter->drawLine(7.33,7.33,42.67,42.67);
  painter->drawLine(7.33,42.67,42.67,7.33);
}

