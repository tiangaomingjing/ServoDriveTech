#include "igraph.h"
#include "igraph_p.h"
#include "boxitemmapping.h"
#include "Option"

#include <QDoubleSpinBox>

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

IGraph::IGraph(QWidget *parent) :QWidget(parent),
  d_ptr(new IGraphPrivate)
{
  d_ptr->q_ptr=this;
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
  setUiVersionName();
  visitActive(uiWidget);
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
