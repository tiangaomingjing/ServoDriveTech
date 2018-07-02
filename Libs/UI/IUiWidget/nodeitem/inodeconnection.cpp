#include "inodeconnection.h"
#include "nodeport.h"


INodeConnection::INodeConnection(NodePort *p1, NodePort *p2, INodeConnection::LineDir dir,bool hasArrow, QGraphicsItem *parent):
  QGraphicsPolygonItem(parent),
  m_port1(p1),
  m_port2(p2),
  m_pos1(QPointF(0,0)),
  m_pos2(QPointF(0,0)),
  m_dir(dir),
  m_hasArrow(hasArrow),
  m_color(Qt::gray),
  m_text("")
{
  m_port1->addNodeConnection(this);
  m_port2->addNodeConnection(this);
  qDebug()<<"INodeConnection construct";
}

INodeConnection::~INodeConnection()
{
  if(m_port1)
    m_port1->removeNodeConnection(this);
  if(m_port2)
    m_port2->removeNodeConnection(this);
}


void INodeConnection::setPort1(NodePort *p)
{
  m_port1->removeNodeConnection(this);
  p->addNodeConnection(this);
  m_port1 = p;
  updatePath();
}

void INodeConnection::setPort2(NodePort *p)
{
  m_port2->removeNodeConnection(this);
  p->addNodeConnection(this);
  m_port2 = p;
  updatePath();
}

NodePort *INodeConnection::port1() const
{
  return m_port1;
}

NodePort *INodeConnection::port2() const
{
  return m_port2;
}

bool INodeConnection::hasArrow() const
{
  return m_hasArrow;
}

void INodeConnection::setHasArrow(bool hasArrow)
{
  m_hasArrow = hasArrow;
  updatePath();
}

INodeConnection::LineDir INodeConnection::dir() const
{
  return m_dir;
}

void INodeConnection::setDir(const LineDir &dir)
{
  m_dir = dir;
  updatePath();
}

QColor INodeConnection::color() const
{
  return m_color;
}

void INodeConnection::setColor(const QColor &color)
{
  m_color = color;
  updatePath();
}

QString INodeConnection::text() const
{
  return m_text;
}

void INodeConnection::setText(const QString &text)
{
  m_text = text;
  updatePath();
}

