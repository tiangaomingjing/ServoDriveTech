#include "nodeblock.h"
#include "nodeport.h"

#include <QHBoxLayout>
#include <QWidget>

#define MIN_W 20
#define MIN_H 20

NodeBlock::NodeBlock(QGraphicsItem *parent) : QGraphicsProxyWidget(parent)
{
  setFlag(QGraphicsItem::ItemIsMovable);
  setFlag(QGraphicsItem::ItemIsSelectable);
  m_leftPort = new NodePort(this);
  m_rightPort = new NodePort(this);
  m_topPort = new NodePort(this);
  m_bottomPort = new NodePort(this);
  QBrush b(Qt::blue);
  m_leftPort->setBrush(b);
  m_rightPort->setBrush(b);
  m_topPort->setBrush(b);
  m_bottomPort->setBrush(b);
  connect(this,SIGNAL(geometryChanged()),this,SLOT(onGeometryChanged()));
}

NodeBlock::~NodeBlock()
{

}

void NodeBlock::setCenterWidget(QWidget *widget, bool hasWrapWidget)
{
  if(hasWrapWidget)
  {
    QWidget *top=new QWidget;
    QPalette p;
    p.setBrush(QPalette::Window,QBrush(Qt::transparent));
    top->setPalette(p);
    QHBoxLayout *layout=new QHBoxLayout(top);
    layout->addWidget(widget);
    layout->setMargin(0);
    top->setLayout(layout);
    QGraphicsProxyWidget::setWidget(top);
  }
  else
    QGraphicsProxyWidget::setWidget(widget);
  setZValue(100);
}

void NodeBlock::onGeometryChanged()
{
  static int i = 0;
  qDebug()<<"geometry changed i = "<<i;
  setPortsPosition();
  i++;
}

void NodeBlock::setPortsPosition()
{
  qreal w=boundingRect().width();
  qreal h=boundingRect().height();
  if(w<MIN_W)
    w = MIN_W;
  if(h<MIN_H)
    h = MIN_H;

  qDebug()<<"w"<<w<<"h"<<h;
  qreal d = m_leftPort->rect().width();
  qreal r = d/2;
  QPointF left(-d,h/2 - r);
  QPointF right(w ,h/2 - r);
  QPointF top(w/2-r,0-d);
  QPointF bottom(w/2-r,h);

  m_leftPort->setPos(left);
  m_rightPort->setPos(right);
  m_topPort->setPos(top);
  m_bottomPort->setPos(bottom);
}

NodePort *NodeBlock::bottomPort() const
{
  return m_bottomPort;
}


NodePort *NodeBlock::topPort() const
{
  return m_topPort;
}

NodePort *NodeBlock::rightPort() const
{
  return m_rightPort;
}

NodePort *NodeBlock::leftPort() const
{
  return m_leftPort;
}

