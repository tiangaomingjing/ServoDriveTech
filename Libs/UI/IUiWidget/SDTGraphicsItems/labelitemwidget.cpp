#include "labelitemwidget.h"
#include <QMouseEvent>
#include <QDebug>

LabelItemWidget::LabelItemWidget(QWidget *parent, Qt::WindowFlags f):QLabel(parent,f)
{

}

LabelItemWidget::LabelItemWidget(const QString &text, QWidget *parent, Qt::WindowFlags f):QLabel(text,parent,f)
{

}

LabelItemWidget::~LabelItemWidget()
{
  qDebug()<<"LabelItemWidget destruct-->";
}

void LabelItemWidget::mousePressEvent(QMouseEvent *event)
{
  if(event->button()==Qt::LeftButton)
  {
    qDebug()<<"emit clicked";
    emit clicked();
  }
}

