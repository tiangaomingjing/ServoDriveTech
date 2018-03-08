#include "igraph.h"
#include "igraph_p.h"
#include "boxitemmapping.h"
#include "Option"
#include "iuiwidget.h"
#include "sevdevice.h"

#include <QEvent>
#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <QDebug>

IGraphPrivate::IGraphPrivate():
  m_dev(NULL),
  m_treeWidget(NULL),
  m_mapping(new BoxItemMapping)
{

}

IGraphPrivate::~IGraphPrivate()
{
  delete m_mapping;
}

IGraph::~IGraph()
{
  delete d_ptr;
}
IGraph::IGraph(IGraphPrivate &dd,QWidget *parent):d_ptr(&dd),QWidget(parent)
{
  d_ptr->q_ptr=this;
}

void IGraph::visit(IUiWidget *uiWidget)
{
  Q_D(IGraph);

  d->m_dev=uiWidget->device();
  int axis=uiWidget->uiIndexs().axisInx;
  int page=uiWidget->uiIndexs().pageInx;
  d->m_treeWidget=d->m_dev->axisTreeSource(axis,page);
  d->m_uiWidget=uiWidget;

  setUiVersionName();

  installDoubleSpinBoxEventFilter();

  setupDataMappings();

  setupConnections();

  setEditTextStatusDefaultAll();

  setCustomVisitActive(uiWidget);
}
void IGraph::syncTreeDataToUiFace()
{

}
void IGraph::setEditTextStatus(QDoubleSpinBox *box, int status)
{
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  face->setEditTextStatus(box,(OptFace::EditTextStatus)status);
}
void IGraph::setEditTextStatusDefaultAll()
{
  Q_D(IGraph);
  foreach (QDoubleSpinBox *box, d->m_mapping->boxLists())
  {
    setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_DEFAULT);
//    setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
  }
}

void IGraph::installDoubleSpinBoxEventFilter()
{
  QList<QDoubleSpinBox *> allBox = findChildren<QDoubleSpinBox *>();
  qDebug()<<"all box count="<<allBox.count();
  foreach (QDoubleSpinBox *box, allBox) {
    box->installEventFilter(this);
    connect(box,SIGNAL(editingFinished()),this,SLOT(onDoubleSpinBoxFocusOut()));
  }
}

bool IGraph::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type()==QEvent::KeyPress)
  {
    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
    {
      Q_D(IGraph);
      qDebug()<<"enter clicked"<<"object name"<<obj->objectName();
      QDoubleSpinBox* box=dynamic_cast<QDoubleSpinBox*>(obj);
      d->m_mapping->syncBoxText2Item(box);
      setEditTextStatus(box,OptFace::EDIT_TEXT_STATUS_READY);
      return true;
    }
  }
  return QWidget::eventFilter(obj,event);
}

void IGraph::setupConnections()
{
  Q_D(IGraph);
  connect(d->m_dev,SIGNAL(itemRangeValid(QTreeWidgetItem*,int)),this,SLOT(onItemBoxEditTextError(QTreeWidgetItem*,int)));
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  connect(face,SIGNAL(faceCssChanged(QString)),this,SLOT(onFaceCssChanged(QString)));
}

void IGraph::onItemBoxEditTextError(QTreeWidgetItem *item, int status)
{
  Q_D(IGraph);
  QDoubleSpinBox *box=d->m_mapping->box(item);
  if(box!=NULL)
    setEditTextStatus(box,OptFace::EditTextStatus(status));
}

void IGraph::onFaceCssChanged(const QString &css)
{
  Q_UNUSED(css);
  setEditTextStatusDefaultAll();
}

void IGraph::onDoubleSpinBoxFocusOut()
{
  Q_D(IGraph);
  QDoubleSpinBox *box=qobject_cast<QDoubleSpinBox *>(sender());
  QTreeWidgetItem *item=d->m_mapping->item(box);
  d->m_mapping->syncItem2BoxText(item);
  qDebug()<<"focus out"<<box;
}
