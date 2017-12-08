#include "iuiwidget.h"
#include "iuiwidget_p.h"
#include <QTreeWidget>

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
  return true;
}

void IUiWidget::setTreeWidget(QTreeWidget *tree)
{

}
