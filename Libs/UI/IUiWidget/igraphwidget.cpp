#include "igraphwidget.h"
#include "igraphwidget_p.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>
#include <QDebug>
IGraphWidgetPrivate::IGraphWidgetPrivate()
{

}
IGraphWidgetPrivate::~IGraphWidgetPrivate()
{
  qDebug()<<"IGraphWidgetPrivate destruct-->";
}

IGraphWidget::IGraphWidget(QWidget *parent) : InteractiveView(parent),
  d_ptr(new IGraphWidgetPrivate)
{
  d_ptr->q_ptr=this;
  Q_D(IGraphWidget);

  d->m_scene=new QGraphicsScene(this);
  d->m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//  d->m_scene->setSceneRect(-200, -200, 400, 400);
  setScene(d->m_scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(1), qreal(1));
//  setMinimumSize(400, 400);

  QGraphicsRectItem *item = new QGraphicsRectItem(QRectF(0, 0, 60, 60));
  d->m_scene->addItem (item);

  QPen pen;               //定义一个画笔
  pen.setWidth (3);       //设置画笔的宽度
  pen.setColor (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item->setPen (pen);
  item->setBrush (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

  item->setPos (qrand () % ((int)d->m_scene->sceneRect ().width ()) - 200,
                qrand () % ((int)d->m_scene->sceneRect ().height ()) - 200);

  QBrush brush(QColor(113,113,113));
  setBackgroundBrush(brush);
}

IGraphWidget::~IGraphWidget()
{
  qDebug()<<"IGraphWidget destruct-->";
  delete d_ptr;
}
IGraphWidget::IGraphWidget(IGraphWidgetPrivate &dd,QWidget *parent):InteractiveView(parent),d_ptr(&dd)
{
  d_ptr->q_ptr=this;
  Q_D(IGraphWidget);

  d->m_scene=new QGraphicsScene(this);
  d->m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//  d->m_scene->setSceneRect(-200, -200, 400, 400);
  setScene(d->m_scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(1), qreal(1));
//  setMinimumSize(400, 400);

  QGraphicsRectItem *item = new QGraphicsRectItem(QRectF(0, 0, 60, 60));
  d->m_scene->addItem (item);

  QPen pen;               //定义一个画笔
  pen.setWidth (3);       //设置画笔的宽度
  pen.setColor (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item->setPen (pen);
  item->setBrush (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

  item->setPos (qrand () % ((int)d->m_scene->sceneRect ().width ()) - 200,
                qrand () % ((int)d->m_scene->sceneRect ().height ()) - 200);

  QBrush brush(backGroundColor());
  setBackgroundBrush(brush);
}

void IGraphWidget::visit(IUiWidget *uiWidget)
{
  setUiVersionName();
  visitActive(uiWidget);
}

QColor IGraphWidget::backGroundColor() const
{
  Q_D(const IGraphWidget);
  return d->m_backGroundColor;
}

void IGraphWidget::setBackGroundColor(const QColor &color)
{
  Q_D(IGraphWidget);
  d->m_backGroundColor=color;
  emit backGroundColorChanged(color);
}

QColor IGraphWidget::arrowColor() const
{
  Q_D(const IGraphWidget);
  return d->m_arrowColor;
}

void IGraphWidget::setArrowColor(const QColor &color)
{
  Q_D(IGraphWidget);
  d->m_arrowColor=color;
  emit arrowColorChanged(color);
}

void IGraphWidget::setCustumBackgroundColor()
{
  QBrush brush(backGroundColor());
  setBackgroundBrush(brush);
}
