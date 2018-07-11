#ifndef SUMITEM_H
#define SUMITEM_H
#include <QGraphicsItem>

class SumItem:public QGraphicsItem
{
public:
  SumItem(QGraphicsItem *parent = 0);
  ~SumItem();

  QRectF boundingRect() const Q_DECL_OVERRIDE;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
};

#endif // SUMITEM_H
