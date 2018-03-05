#include "targetitemwidget.h"

#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QPaintEvent>
#include <QStyleOption>

TargetItemWidget::TargetItemWidget(QWidget *parent) : QWidget(parent),
  m_penColor(Qt::blue)
{

}

TargetItemWidget::~TargetItemWidget()
{

}

QSize TargetItemWidget::sizeHint() const
{
  int width=fontMetrics().width("m")*1;
  return QSize(width,width);
}

QColor TargetItemWidget::penColor() const
{
  return m_penColor;
}

void TargetItemWidget::setPenColor(const QColor &penColor)
{
  m_penColor = penColor;
  emit penColorChanged(m_penColor);
}

void TargetItemWidget::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  QStyleOption opt;
  opt.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

  painter.setRenderHint(QPainter::Antialiasing,true);
  QPen pen;
  pen.setWidth(1);
  pen.setColor(penColor());
  painter.setPen(pen);
  painter.setBrush(QBrush(penColor()));
  int w=width();
  qreal adjust=0.5;
  QRectF rect(0+adjust,0+adjust,w-adjust*2,w-adjust*2);
  painter.drawEllipse(rect);
}

