#include "iuiwidget.h"
#include "iuiwidget_p.h"

#include <QTreeWidget>
#include <QStackedWidget>

IUiWidget::IUiWidget(QWidget *parent):QWidget(parent),d_ptr(new IUiWidgetPrivate())
{
  d_ptr->q_ptr=this;
}
IUiWidget::~IUiWidget()
{

}
IUiWidget::IUiWidget(IUiWidgetPrivate &d,QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
bool IUiWidget::init()
{
  Q_D(IUiWidget);
  d->m_uiStackedWidget=getUiStackedWidget();
  setCurrentUiIndex(1);
  return true;
}
void IUiWidget::setCurrentUiIndex(quint8 index)
{
  Q_D(IUiWidget);
  quint8 inx=index;
  if(inx>d->m_uiStackedWidget->count()-1)
    inx=d->m_uiStackedWidget->count()-1;
  d->m_uiStackedWidget->setCurrentIndex(inx);
}

void IUiWidget::setTreeWidget(QTreeWidget *tree)
{

}
void IUiWidget::setUiIndexs(quint8 axisInx, quint8 pageInx, quint8 sdInx)
{
  Q_D(IUiWidget);
  d->axisInx=axisInx;
  d->pageInx=pageInx;
  d->sdInx=sdInx;
}
