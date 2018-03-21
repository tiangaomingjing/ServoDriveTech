#include "ledalarm.h"

#include <QMenu>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>

LedAlarm::LedAlarm(const QString &name, QWidget *parent, quint16 id, LedTextPosition pos) : QWidget(parent),
  m_id(id),
  m_label(new QLabel(name,this)),
  m_menuActive(false),
  m_led(new LedAlarm::Led(this))
{
  QLayout *layout=NULL;
  if(pos==LED_TEXT_BOTTOM)
  {
    layout=new QVBoxLayout(this);
  }
  else
  {
    layout=new QHBoxLayout(this);
  }
  layout->addWidget(m_led);
  layout->addWidget(m_label);
  setLayout(layout);
}

LedAlarm::~LedAlarm()
{
}

void LedAlarm::setLedName(const QString &name)
{
  m_label->setText(name);
}

void LedAlarm::addMenuAction(QAction *action)
{
  m_led->menu()->addAction(action);
}

bool LedAlarm::menuActive() const
{
  return m_menuActive;
}

void LedAlarm::setMenuActive(bool active)
{
  m_menuActive = active;
  m_led->menu()->setEnabled(active);
}

void LedAlarm::setError(bool error)
{
  m_led->setError(error);
}


LedAlarm::Led::Led(LedAlarm *parent):QPushButton(parent),
  m_menu(new QMenu(this)),
  m_parent(parent),
  m_passColor(Qt::green),
  m_errorColor(Qt::red),
  m_hasError(false)
{
  setMenu(m_menu);
  setStyleSheet("background-color:yellow");
  setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
}

LedAlarm::Led::~Led()
{

}

QSize LedAlarm::Led::sizeHint() const
{
  int width=fontMetrics().width("m")*2;
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
//  painter.setPen(pen);
  painter.setBrush(QBrush(color));

  QColor frameColor=color.lighter();

  int w=width();
  qreal adjust=pen.width()/2;
  painter.drawEllipse(0+adjust,0+adjust,w-adjust*2,w-adjust*2);

  pen.setColor(frameColor);
  painter.setPen(pen);
  painter.drawEllipse(0+adjust,0+adjust,w-adjust*2,w-adjust*2);
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

