#include "itabwidget.h"
#include "sevdevice.h"

ITabWidget::ITabWidget(const QString &name,int axisCount ,SevDevice *sev,QWidget *parent) : QWidget(parent),
  m_name(name),
  m_axisCount(axisCount),
  m_sevDevice(sev)
{

}

QString ITabWidget::name() const
{
  return m_name;
}

void ITabWidget::setName(const QString &name)
{
  m_name = name;
}

int ITabWidget::axisCount() const
{
  return m_axisCount;
}

void ITabWidget::setAxisCount(int axisCount)
{
  m_axisCount = axisCount;
}

