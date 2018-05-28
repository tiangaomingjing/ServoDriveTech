#include "igraphwidget.h"
#include "igraphwidget_p.h"
#include "boxitemmapping.h"
#include "Option"
#include "iuiwidget.h"
#include "sevdevice.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>
#include <QDebug>
#include <QEvent>
#include <QDoubleSpinBox>
#include <QKeyEvent>

IGraphWidget::~IGraphWidget()
{
  Q_D(IGraphWidget);
  delete d->m_scene;
  qDebug()<<"IGraphWidget destruct-->";
  delete d_ptr;
}
IGraphWidget::IGraphWidget(IGraphWidgetPrivate &dd,QWidget *parent):InteractiveView(parent),d_ptr(&dd)
{
  d_ptr->q_ptr=this;
  Q_D(IGraphWidget);

  d->m_scene=new QGraphicsScene;
  d->m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
//  d->m_scene->setSceneRect(-200, -200, 400, 400);
  setScene(d->m_scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(1), qreal(1));
//  setMinimumSize(400, 400);

//  QGraphicsRectItem *item = new QGraphicsRectItem(QRectF(0, 0, 60, 60));
//  d->m_scene->addItem (item);

//  QPen pen;               //定义一个画笔
//  pen.setWidth (3);       //设置画笔的宽度
//  pen.setColor (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
//  item->setPen (pen);
//  item->setBrush (QColor(qrand() % 256, qrand() % 256, qrand() % 256));
//  item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

//  item->setPos (qrand () % ((int)d->m_scene->sceneRect ().width ()) - 200,
//                qrand () % ((int)d->m_scene->sceneRect ().height ()) - 200);

  QBrush brush(backGroundColor());
  setBackgroundBrush(brush);
}

void IGraphWidget::visit(IUiWidget *uiWidget)
{
  Q_D(IGraphWidget);

  d->m_dev=uiWidget->device();
  int axis=uiWidget->uiIndexs().axisInx;
  int page=uiWidget->uiIndexs().pageInx;
  d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);
  d->m_uiWidget=uiWidget;

  setUiVersionName();

  createItems();

  setupDataMappings();

  installDoubleSpinBoxEventFilter();

  setDoubleSpinBoxConnections();

  setCommonConnections();

  setEditTextStatusDefaultAll();

  setCustomVisitActive(uiWidget);
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


void IGraphWidget::setEditTextStatus(QDoubleSpinBox *box, int status)
{
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  face->setEditTextStatus(box,(OptFace::EditTextStatus)status);
}

void IGraphWidget::setEditTextStatusDefaultAll()
{
  Q_D(IGraphWidget);
  foreach (QDoubleSpinBox *box, d->m_mapping->boxLists())
  {
    setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_DEFAULT);
  }
}

//bool IGraphWidget::eventFilter(QObject *obj, QEvent *event)
//{
//  qDebug()<<"IGraphWidget::eventFilter";
//  if (event->type()==QEvent::KeyPress)
//  {
//    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
//    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
//    {
//      Q_D(IGraphWidget);
//      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
//      QDoubleSpinBox* box=dynamic_cast<QDoubleSpinBox*>(obj);
//      d->m_mapping->syncBoxText2Item(box);
////      d->m_mapping->syncBoxText2MultiItem(box);
//      setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
//      return true;
//    }
//  }
//  return InteractiveView::eventFilter(obj,event);
//}

void IGraphWidget::setCommonConnections()
{
  Q_D(IGraphWidget);
  connect(d->m_dev,SIGNAL(itemRangeValid(QTreeWidgetItem*,int)),this,SLOT(onItemBoxEditTextError(QTreeWidgetItem*,int)));
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onFaceCssChanged(QString)));
}

void IGraphWidget::onItemBoxEditTextError(QTreeWidgetItem *item, int status)
{
  Q_D(IGraphWidget);
  QDoubleSpinBox *box=d->m_mapping->box(item);
  if(box!=NULL)
    setEditTextStatus(box,OptFace::EditTextStatus(status));
}

void IGraphWidget::onFaceCssChanged(const QString &css)
{
  Q_UNUSED(css);
  adjustPosition();
  setCustumBackgroundColor();
}

void IGraphWidget::onDoubleSpinBoxFocusOut()
{
  Q_D(IGraphWidget);
  QDoubleSpinBox *box=qobject_cast<QDoubleSpinBox *>(sender());
  QTreeWidgetItem *item=d->m_mapping->item(box);
  d->m_mapping->syncItem2BoxText(item);
  qDebug()<<"focus out"<<box;
}
