#include "iuiwidget.h"
#include "iuiwidget_p.h"


#include <QTreeWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDebug>

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
bool IUiWidget::init(SevDevice *device)
{
  Q_D(IUiWidget);
  d->m_uiStackedWidget=getUiStackedWidget();
  d->m_vboxLayout=getVBoxLayout();
  d->m_device=device;

  setDefaultUi();

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

void IUiWidget::addTreeWidget(QTreeWidget *tree)
{
  Q_D(IUiWidget);
  d->m_dataTree=tree;
  d->m_vboxLayout->addWidget(tree);
}
void IUiWidget::setUiIndexs(quint8 axisInx, quint8 pageInx)
{
  Q_D(IUiWidget);
  d->axisInx=axisInx;
  d->pageInx=pageInx;
}
void IUiWidget::readFLASH()
{
  Q_D(IUiWidget);
  qDebug()<<this->objectName()<<"read flash";
  emit sglReadPageFlash(d->axisInx,d->m_dataTree);
//  d->m_device->readPageFlash(d->axisInx,d->m_dataTree);//委托设备去读取
}
void IUiWidget::writeFLASH()
{

}
void IUiWidget::setUiActive(bool actived)
{
  Q_UNUSED(actived);
}
