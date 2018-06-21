#ifndef NODESWITCH_H
#define NODESWITCH_H
#include <QGraphicsPathItem>

class NodePort;
class NodeSwitch : public QGraphicsPathItem
{
public:
  explicit NodeSwitch(QGraphicsItem *parent = 0);
  ~NodeSwitch();

  NodePort *leftPort() const;

  NodePort *topPort() const;

  NodePort *bottomPort() const;

  void setPortColor(const QColor &clr);
  void setPortBrushColor(const QColor &clr);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

  void setPenColor(const QColor &penColor);

  void setBrushColor(const QColor &brushColor);

  void setBrushSelectedColor(const QColor &brushSelectedColor);

  bool isOn() const;
  void setIsOn(bool isOn);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
  NodePort *m_leftPort;
  NodePort *m_topPort;
  NodePort *m_bottomPort;

  QColor m_penColor;
  QColor m_brushColor;
  QColor m_brushSelectedColor;

  bool m_isOn;
};

#endif // NODESWITCH_H
