#include "widgetitem.h"
#include <QGraphicsProxyWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QDebug>

WidgetItem::WidgetItem(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsProxyWidget(parent,wFlags)
{
  for(int i=0;i<4;i++)
    m_netPoints.append(new QPointF(0,0));
  connect(this,SIGNAL(geometryChanged()),this,SLOT(onGeometryChanged()));
//  connect(m_proxyWidget,SIGNAL(destroyed(QObject*)),this,
}

WidgetItem::~WidgetItem()
{
//  if(m_proxyWidget!=NULL)//不能这么操作，因为m_proxyWidget 增加到scene后，它的ownership就由scene控制了，如果再delete,就会再次delete则出错
//    delete m_proxyWidget;
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
    QGraphicsProxyWidget::setWidget(top);
  }
  else
    QGraphicsProxyWidget::setWidget(widget);
}

//QGraphicsProxyWidget *WidgetItem::item() const
//{
//  return m_proxyWidget;
//}

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
  qreal w=boundingRect().width();
  qreal h=boundingRect().height();
  QPointF pos=scenePos();
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

