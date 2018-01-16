#include "iuiwidget.h"
#include "iuiwidget_p.h"
#include "sevdevice.h"
#include "gtutils.h"

#include "Option"

#include <QTreeWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QQuickWidget>
#include <QQmlContext>
#include <QAction>
#include <QQmlEngine>

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
void IUiWidget::setContextAction()
{
  Q_D(IUiWidget);
  d->m_actSwitchView=new QAction(this);
  d->m_actSwitchView->setText(tr("switch to list view"));
  d->m_actSwitchView->setCheckable(true);
  d->m_actSwitchView->setChecked(false);
  connect(d->m_actSwitchView,SIGNAL(triggered(bool)),this,SLOT(onSwitchView(bool)));
  this->addAction(d->m_actSwitchView);
  QAction *actSeparator=new QAction(this);
  actSeparator->setSeparator(true);
  this->addAction(actSeparator);

  d->m_actReadRAM=new QAction(this);
  d->m_actReadRAM->setText(tr("RAM value"));
  connect(d->m_actReadRAM,SIGNAL(triggered(bool)),this,SLOT(onActionReadRAM()));
  this->addAction(d->m_actReadRAM);

  d->m_actReadFLASH=new QAction(this);
  d->m_actReadFLASH->setText(tr("FLASH value"));
  connect(d->m_actReadFLASH,SIGNAL(triggered(bool)),this,SLOT(onActionReadFLASH()));
  this->addAction(d->m_actReadFLASH);
}

void IUiWidget::updateUi()
{
  qDebug()<<this->objectName()<<"updateUi";
}

void IUiWidget::createQmlWidget()
{
  Q_D(IUiWidget);

  d->m_qmlpath=GTUtils::sysPath()+\
      d->m_device->typeName()+"/"+\
      d->m_device->modelName()+"/"+\
      d->m_device->versionName()+"/ui/"+\
      objectName()+".qml";
  d->m_qwidget=new QQuickWidget(this);
  d->m_qwidget->setMinimumSize(600,560);
  qDebug()<<"load qml from:"<<d->m_qmlpath;

  //style context
  QString qmlStyleModulePath=GTUtils::customPath()+"option/qmlstyle/";
  d->m_qwidget->engine()->addImportPath(qmlStyleModulePath);
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QmlStyleHelper *helper=face->qmlStyleHelper();
  d->m_qwidget->rootContext()->setContextProperty("qmlStyleHelper",helper);

  d->m_qwidget->rootContext()->setContextProperty("cDevice",d->m_device);

  setQmlContext();
  d->m_qwidget->setResizeMode(QQuickWidget::SizeRootObjectToView );
  d->m_qwidget->setSource(QUrl::fromLocalFile(d->m_qmlpath));
  setQmlSignalSlot();
  addQmlWidget();
}

bool IUiWidget::hasConfigFunc()
{
  return true;
}
bool IUiWidget::hasSaveFunc()
{
  return true;
}

void IUiWidget::addTreeWidget(QTreeWidget *tree)
{
  Q_D(IUiWidget);
  d->m_dataTree=tree;
  d->m_vboxLayout->addWidget(tree);
  connect(tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onTreeItemClickedEdit(QTreeWidgetItem*,int)));

  setContextAction();
}
void IUiWidget::setUiIndexs(const UiIndexs &indexs)
{
  Q_D(IUiWidget);
  d->m_index=indexs;
}
UiIndexs IUiWidget::uiIndexs() const
{
  Q_D(const IUiWidget);
  return d->m_index;
}
void IUiWidget::readPageFLASH()
{
  Q_D(IUiWidget);
  qDebug()<<this->objectName()<<"read flash";
//  emit sglReadPageFlash(d->axisInx,d->m_dataTree);
  d->m_device->onReadPageFlash(d->m_index.aixsInx,d->m_dataTree);
}
void IUiWidget::writePageFLASH()
{
  Q_D(IUiWidget);
  qDebug()<<this->objectName()<<"read flash";
//  emit sglWritePageFlash(d->axisInx,d->m_dataTree);
  d->m_device->onWritePageFlash(d->m_index.aixsInx,d->m_dataTree);
}
void IUiWidget::setUiActive(bool actived)
{
  if(actived)
    updateUi();
  emit sglQmlActived(actived);
}

void IUiWidget::onTreeItemClickedEdit(QTreeWidgetItem *item, int column)
{
  Q_D(IUiWidget);
  if(column==UI::COL_PAGE_TREE_VALUE)
  {
    if(item->childCount()==0)
    {
      item->setFlags(item->flags()|Qt::ItemIsEditable);
      d->m_dataTree->editItem(item,column);
      qDebug()<<"edit "<<item->text(0);
    }
  }
  else item->setFlags(item->flags()&(~Qt::ItemIsEditable));
  qDebug()<<"clicked";
}

void IUiWidget::onSwitchView(bool isList)
{
  Q_D(IUiWidget);
  if(isList)
  {
    d->m_uiStackedWidget->setCurrentIndex(1);
    d->m_actSwitchView->setText(tr("switch to graph view"));
//    onActionReadFuncValueFromRam();
  }
  else
  {
    d->m_uiStackedWidget->setCurrentIndex(0);
    d->m_actSwitchView->setText(tr("switch to list view"));
  }
}

void IUiWidget::onActionReadRAM()
{
  qDebug()<<"read ram";
}

void IUiWidget::onActionReadFLASH()
{
  qDebug()<<"read flash";
}
