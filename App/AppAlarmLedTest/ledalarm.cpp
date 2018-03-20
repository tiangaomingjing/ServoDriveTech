#include "ledalarm.h"

#include <QMenu>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

LedAlarm::LedAlarm(const QString &name, QWidget *parent, quint16 id, LedTextPosition pos) : QWidget(parent),
  m_menu(new QMenu),
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
  delete m_menu;
}

void LedAlarm::setLedName(const QString &name)
{
  m_label->setText(name);
}

void LedAlarm::addMenuAction(QAction *action)
{
  m_menu->addAction(action);
}

bool LedAlarm::menuActive() const
{
  return m_menuActive;
}

void LedAlarm::setMenuActive(bool active)
{
  m_menuActive = active;
  m_menu->setEnabled(active);
}


LedAlarm::Led::Led(LedAlarm *parent):QPushButton(parent),
  m_menu(new QMenu(this)),
  m_parent(parent)
{
  connect(this,SIGNAL(clicked(bool)),SLOT(onBtnClicked()));
}

LedAlarm::Led::~Led()
{

}

void LedAlarm::Led::onBtnClicked()
{
  if(m_parent->m_menuActive){
    setMenu(m_parent->m_menu);
    menu()->exec();
  }
}
