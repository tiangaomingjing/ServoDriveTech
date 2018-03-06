#include "sumitemwidget.h"

#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QPaintEvent>
#include <QStyleOption>

SumItemWidget::SumItemWidget(QWidget *parent) : QWidget(parent),
  m_lineColor(Qt::black)
{

}

SumItemWidget::~SumItemWidget()
{

}

QSize SumItemWidget::sizeHint() const
{
  int width=fontMetrics().width("m")*5;
  return QSize(width,width);
}

QColor SumItemWidget::lineColor() const
{
  return m_lineColor;
}

void SumItemWidget::setLineColor(const QColor &color)
{
  if(m_lineColor!=color)
  {
    m_lineColor=color;
    emit lineColorChanged(m_lineColor);
  }
}

void SumItemWidget::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  QStyleOption opt;
  opt.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

  painter.setRenderHint(QPainter::Antialiasing,true);
  QPen pen;
  pen.setWidth(2);
  pen.setColor(lineColor());
  painter.setPen(pen);
  int w=width();
  qreal x1,x2;
  qreal adjust=pen.width()/2;
  x1=0.293*w/2+adjust;
  x2=1.707*w/2-adjust;
  QPointF pa(x1,x1);
  QPointF pb(x1,x2);
  QPointF pc(x2,x2);
  QPointF pd(x2,x1);

  painter.drawEllipse(0+adjust,0+adjust,w-adjust*2,w-adjust*2);
  painter.drawLine(pa,pc);
  painter.drawLine(pb,pd);

//  qDebug()<<"paint event rect"<<event->rect();
}


