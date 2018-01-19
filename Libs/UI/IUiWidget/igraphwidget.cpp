#include "igraphwidget.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>

IGraphWidget::IGraphWidget(QWidget *parent) : QGraphicsView(parent)
{
  m_scene=new QGraphicsScene(this);
  m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  m_scene->setSceneRect(-200, -200, 400, 400);
  setScene(m_scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(0.8), qreal(0.8));
  setMinimumSize(400, 400);

  QGraphicsRectItem *item = new QGraphicsRectItem(QRectF(0, 0, 60, 60));
  m_scene->addItem (item);

  QPen pen;               //定义一个画笔
  pen.setWidth (3);       //设置画笔的宽度
  pen.setColor (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item->setPen (pen);
  item->setBrush (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
  item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

  item->setPos (qrand () % ((int)m_scene->sceneRect ().width ()) - 200,
                qrand () % ((int)m_scene->sceneRect ().height ()) - 200);

  QBrush brush(QColor(113,113,113));
  setBackgroundBrush(brush);
}

IGraphWidget::~IGraphWidget()
{

}
