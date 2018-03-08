#include "gtdoublespinbox.h"

GtDoubleSpinBox::GtDoubleSpinBox(QObject *parent) : QDoubleSpinBox(parent)
{

}


GtDoubleSpinBox::~GtDoubleSpinBox()
{

}

QColor GtDoubleSpinBox::defaultColor() const
{
  return m_defaultColor;
}

void GtDoubleSpinBox::setDefaultColor(const QColor &defaultColor)
{
  m_defaultColor = defaultColor;
}

QColor GtDoubleSpinBox::readyColor() const
{
  return m_readyColor;
}

void GtDoubleSpinBox::setReadyColor(const QColor &readyColor)
{
  m_readyColor = readyColor;
}

QColor GtDoubleSpinBox::errorColor() const
{
  return m_errorColor;
}

void GtDoubleSpinBox::setErrorColor(const QColor &errorColor)
{
  m_errorColor = errorColor;
}
