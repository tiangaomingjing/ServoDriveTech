﻿#include "ledalarm.h"

#include <QMenu>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QSpacerItem>

LedAlarm::LedAlarm(const QString &name, QWidget *parent, qint16 id, LedTextPosition pos) : QWidget(parent),
  m_id(id),
  m_label(new QLabel(name,this)),
  m_led(new LedAlarm::Led(this))
{
  if(pos==LED_TEXT_BOTTOM)
  {
    QVBoxLayout *vLayout=new QVBoxLayout(this);
    vLayout->addWidget(m_led);
    vLayout->addWidget(m_label);
    m_label->setAlignment(Qt::AlignHCenter);
    vLayout->setStretch(0,0);
    vLayout->setStretch(1,1);
    setLayout(vLayout);
  }
  else
  {
    QHBoxLayout *hLayout=new QHBoxLayout(this);
    hLayout->addWidget(m_led);
    hLayout->addWidget(m_label);
    hLayout->setStretch(0,0);
    hLayout->setStretch(1,1);
    setLayout(hLayout);
  }

}

LedAlarm::~LedAlarm()
{
}

void LedAlarm::setLedName(const QString &name)
{
  m_label->setText(name);
}

void LedAlarm::setError(bool error)
{
  m_led->setError(error);
}

qint16 LedAlarm::id() const
{
  return m_id;
}

LedAlarm::Led::Led(LedAlarm *parent):QWidget(parent),
  m_parent(parent),
  m_passColor(Qt::green),
  m_errorColor(Qt::red),
  m_hasError(false)
{
  setMinimumSize(fontWidth(),fontWidth());
  setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));

}

LedAlarm::Led::~Led()
{

}

QSize LedAlarm::Led::sizeHint() const
{
  int width=fontWidth();
  return QSize(width,width);
}

void LedAlarm::Led::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event);

  QStyleOption opt;
  opt.init(this);
  QPainter painter(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
  painter.setRenderHint(QPainter::Antialiasing,true);
  QPen pen;
  pen.setWidth(2);
  QColor color;
  if(m_hasError)
    color=m_errorColor;
  else
    color=m_passColor;
  pen.setColor(color);
  painter.setPen(pen);
  painter.setBrush(QBrush(color));

  QColor frameColor=color.darker();

  qreal adjust=pen.width()/2;

  qreal x=width()/2;
  qreal y=height()/2;
  QPointF center(x,y);
  qreal r=fontWidth()/2-adjust;

  painter.drawEllipse(center,r,r);

  pen.setColor(frameColor);
  painter.setPen(pen);
  painter.drawEllipse(center,r,r);
}

int LedAlarm::Led::fontWidth() const
{
  return fontMetrics().width("m")*3;
}

QColor LedAlarm::Led::errorColor() const
{
  return m_errorColor;
}

void LedAlarm::Led::setErrorColor(const QColor &errorColor)
{
  m_errorColor = errorColor;
  emit errorColorChanged(m_errorColor);
}

bool LedAlarm::Led::hasError() const
{
  return m_hasError;
}

void LedAlarm::Led::setError(bool error)
{
  if(m_hasError!=error)
  {
    m_hasError=error;
    update();
  }
}

QColor LedAlarm::Led::passColor() const
{
  return m_passColor;
}

void LedAlarm::Led::setPassColor(const QColor &passColor)
{
  m_passColor = passColor;
  emit passColorChanged(m_passColor);
}

