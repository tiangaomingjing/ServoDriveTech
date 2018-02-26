#include "piditem.h"
#include <QGraphicsProxyWidget>
#include <QGraphicsLinearLayout>
#include <QWidget>
#include <QHBoxLayout>
#include <QDebug>

PidItem::PidItem(QObject *parent ) : QObject(parent),
  m_proxyWidget(new QGraphicsProxyWidget)
{
  m_proxyWidget->installEventFilter(this);
}

PidItem::~PidItem()
{
  delete m_proxyWidget;
  qDebug()<<"pid destruct-->";
}

void PidItem::setWidget(QWidget *widget)
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

  qDebug()<<"set widget------------------";
  qDebug()<<"proxyWidget pos"<<m_proxyWidget->pos();
  qreal width=m_proxyWidget->boundingRect().width();
  qreal height=m_proxyWidget->boundingRect().height();
  qreal x=m_proxyWidget->pos().x();
  qreal y=m_proxyWidget->pos().y();
  qDebug()<<"left:"<<QString("(%1,%2)").arg(x).arg(y+height/2);
  qDebug()<<"right:"<<QString("(%1,%2)").arg(x+width).arg(y+height/2);
  qDebug()<<"top:"<<QString("(%1,%2)").arg(x+width/2).arg(y);
  qDebug()<<"bottom:"<<QString("(%1,%2)").arg(x+width/2).arg(y+height);
  qDebug()<<"set widget------------------end";
}

QGraphicsProxyWidget *PidItem::item()
{
  return m_proxyWidget;
}

bool PidItem::eventFilter(QObject *obj, QEvent *e)
{
  if(obj==m_proxyWidget)
  {
    if(e->type()==QEvent::GraphicsSceneResize)
    {
      qDebug()<<"proxyWidget resize event";
      qDebug()<<"proxyWidget resize bounding rect"<<m_proxyWidget->boundingRect();
      qDebug()<<"proxyWidget pos"<<m_proxyWidget->pos();
      qreal width=m_proxyWidget->boundingRect().width();
      qreal height=m_proxyWidget->boundingRect().height();
      qreal x=m_proxyWidget->pos().x();
      qreal y=m_proxyWidget->pos().y();
      qDebug()<<"left:"<<QString("(%1,%2)").arg(x).arg(y+height/2);
      qDebug()<<"right:"<<QString("(%1,%2)").arg(x+width).arg(y+height/2);
      qDebug()<<"top:"<<QString("(%1,%2)").arg(x+width/2).arg(y);
      qDebug()<<"bottom:"<<QString("(%1,%2)").arg(x+width/2).arg(y+height);
//      return true;
    }
  }
  return QObject::eventFilter(obj,e);
}
