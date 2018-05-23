#include "itabwidget.h"
#include "sevdevice.h"

ITabWidget::ITabWidget(const QString &name, SevDevice *sev, QWidget *parent) : QWidget(parent),
  m_name(name),
  m_axisCount(sev->axisNum()),
  m_sev(sev)
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

SevDevice *ITabWidget::sevDevice() const
{
  return m_sev;
}

void ITabWidget::setSevDevice(SevDevice *sevDevice)
{
  m_sev = sevDevice;
}

