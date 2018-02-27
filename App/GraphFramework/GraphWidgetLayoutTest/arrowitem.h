#ifndef ARROWITEM_H
#define ARROWITEM_H

#include <QGraphicsPolygonItem>

class ArrowItem : public QGraphicsPolygonItem
{
public:
  enum ArrowType{
    ARROW_TYPE_STRAIGHT,
    ARROW_TYPE_CORNER
  };
  explicit ArrowItem(QPointF *startPoint,QPointF *endPoint,ArrowType type = ARROW_TYPE_STRAIGHT ,const QString &text = "",QGraphicsItem *parent=0);
  ~ArrowItem();
  void updatePosition();
  void setColor(const QColor &color);

  void setText(const QString &text);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
  QPolygonF calculatePolygon();

private:
  enum ArrowDir{
    ARROW_DIR_LEFT_UP,
    ARROW_DIR_LEFT_DOWN,
    ARROW_DIR_RIGHT_UP,
    ARROW_DIR_RIGHT_DOWN
  };

  QPointF *m_startPoint;
  QPointF *m_endPoint;
  QPointF *m_cornerPoint;
  QColor m_color;
  ArrowType m_type;
  QString m_text;
};

#endif // ARROWITEM_H
