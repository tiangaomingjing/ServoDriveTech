#include "widgetitem.h"
#include <QGraphicsProxyWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QDebug>

WidgetItem::WidgetItem(QObject *parent) : QObject(parent),
  m_proxyWidget(new QGraphicsProxyWidget)
{
  for(int i=0;i<4;i++)
    m_netPoints.append(new QPointF(0,0));
  connect(m_proxyWidget,SIGNAL(geometryChanged()),this,SLOT(onGeometryChanged()));
}

WidgetItem::~WidgetItem()
{
  delete m_proxyWidget;
  foreach (QPointF *p, m_netPoints) {
    delete p;
  }
  m_netPoints.clear();
  qDebug()<<"WidgetItem destruct-->";
}

void WidgetItem::setWidget(QWidget *widget, bool hasWrapWidget)
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
    m_proxyWidget->setWidget(top);
  }
  else
    m_proxyWidget->setWidget(widget);
}

QGraphicsProxyWidget *WidgetItem::item() const
{
  return m_proxyWidget;
}

QPointF *WidgetItem::pointF(int index) const
{
  if(index<m_netPoints.count())
    return m_netPoints.at(index);
  else
    return NULL;
}

void WidgetItem::onGeometryChanged()
{
//  qDebug()<<"***************"<<objectName()<<"onGeometryChanged"<<m_proxyWidget->boundingRect()<<"************";
  qreal w=m_proxyWidget->boundingRect().width();
  qreal h=m_proxyWidget->boundingRect().height();
  QPointF pos=m_proxyWidget->scenePos();
//  qDebug()<<"w"<<w<<"h"<<h<<" scenePos"<<pos;
  QPointF left(0,h/2);
  QPointF right(w,h/2);
  QPointF top(w/2,0);
  QPointF bottom(w/2,h);
//  qDebug()<<"size"<<m_netPoints.size();
  *m_netPoints[POINT_TYPE_LEFT]=left+pos;
  *m_netPoints[POINT_TYPE_RIGHT]=right+pos;
  *m_netPoints[POINT_TYPE_TOP]=top+pos;
  *m_netPoints[POINT_TYPE_BOTTOM]=bottom+pos;
//  for(int i=0;i<m_netPoints.size();i++)
//    qDebug()<<i<<*(m_netPoints.at(i));
}

