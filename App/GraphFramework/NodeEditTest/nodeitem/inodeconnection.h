#ifndef INODECONNECTION_H
#define INODECONNECTION_H
#include <QGraphicsPolygonItem>
#include "nodeitemglobaldef.h"
class NodePort;
class INodeConnection : public QGraphicsPolygonItem
{
public:
  enum { Type = NodeItem::NODE_CONNECT };
  typedef enum {
    DIR_UP,
    DIR_DOWN
  }LineDir;
  explicit INodeConnection(NodePort*p1,NodePort*p2,LineDir dir = DIR_UP,bool hasArrow = true ,QGraphicsItem * parent = 0);
  virtual ~INodeConnection();

  void setPort1(NodePort *p);
  void setPort2(NodePort *p);
  virtual void updatePath() = 0;
  NodePort *port1() const;
  NodePort *port2() const;

  int type() const { return Type; }

  bool hasArrow() const;
  void setHasArrow(bool hasArrow);

  LineDir dir() const;
  void setDir(const LineDir &dir);

  QColor color() const;
  void setColor(const QColor &color);

  QString text() const;
  void setText(const QString &text);
protected:
  void updatePos12();

protected:
  NodePort *m_port1;
  NodePort *m_port2;
  QPointF m_pos1;
  QPointF m_pos2;
  LineDir m_dir;
  bool m_hasArrow;
  QColor m_color;
  QString m_text;
};

#endif // INODECONNECTION_H
