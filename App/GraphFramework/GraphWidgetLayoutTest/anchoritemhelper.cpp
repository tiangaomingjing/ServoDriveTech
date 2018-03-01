#include "anchoritemhelper.h"
#include <QGraphicsItem>

class AnchorItemHelper::AnchorData
{
public:
  QGraphicsItem *originItem;
  QGraphicsItem *targetItem;
  AnchorItemHelper::AnchorPoint anchorPoint;
  qreal space;
};

AnchorItemHelper::AnchorItemHelper(QObject *parent) : QObject(parent)
{

}

AnchorItemHelper::~AnchorItemHelper()
{
  foreach (AnchorItemHelper::AnchorData *data, m_anchorDatas) {
    delete data;
  }
  m_anchorDatas.clear();
}

void AnchorItemHelper::addAnchor(QGraphicsItem *originItem, QGraphicsItem *targetItem, AnchorItemHelper::AnchorPoint anchorPoint, qreal space)
{
  AnchorItemHelper::AnchorData *data=new AnchorItemHelper::AnchorData;
  data->originItem=originItem;
  data->targetItem=targetItem;
  data->anchorPoint=anchorPoint;
  data->space=space;

  m_anchorDatas.append(data);
}

void AnchorItemHelper::setAnchorsActive()
{
  QPointF *p0,*p1;
  qreal x,y,space;
  QGraphicsItem *originItem;
  QGraphicsItem *targetItem;
  foreach (AnchorItemHelper::AnchorData *data, m_anchorDatas)
  {
    originItem=data->originItem;
    targetItem=data->targetItem;
    p0=&(originItem->pos());
    p1=&(targetItem->pos());
    space=data->space;
    switch (data->anchorPoint)
    {
    case AnchorLeft:
      x=p0->x()+space;
      y=p1->y();
      break;
    case AnchorHorizontalCenter:
      x=p0->x()+originItem->boundingRect().width()/2-targetItem->boundingRect().width()/2+space;
      y=p1->y();
      break;
    case AnchorRight:
      x=p0->x()+originItem->boundingRect().width()-targetItem->boundingRect().width()+space;
      y=p1->y();
      break;
    case AnchorTop:
      x=p1->x();
      y=p0->y()+space;
      break;
    case AnchorVerticalCenter:
      x=p1->x();
      y=p0->y()+originItem->boundingRect().height()/2-targetItem->boundingRect().height()/2+space;
      break;
    case AnchorBottom:
      x=p1->x();
      y=p0->y()+originItem->boundingRect().height()-targetItem->boundingRect().height()+space;
      break;
    default:
      break;
    }
    targetItem->setPos(x,y);
  }
}

