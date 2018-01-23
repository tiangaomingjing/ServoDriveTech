#include "stylewidget.h"

StyleWidget::StyleWidget(QWidget *parent) : QWidget(parent)
{

}

QColor StyleWidget::dsBoxBackgroundDefColor() const
{
  return m_dsBoxBackgroundDefColor;
}

void StyleWidget::setdsBoxBackgroundDefColor(const QColor &dsBoxBackgroundDefColor)
{
  if(m_dsBoxBackgroundDefColor != dsBoxBackgroundDefColor)
  {
    m_dsBoxBackgroundDefColor = dsBoxBackgroundDefColor;
    emit dsBoxBackgroundDefColorChanged(m_dsBoxBackgroundDefColor);
  }
}

QColor StyleWidget::dsBoxTextEditColor() const
{
  return m_dsBoxTextEditColor;
}

void StyleWidget::setdsBoxTextEditColor(const QColor &dsBoxTextEditColor)
{
  if(m_dsBoxTextEditColor != dsBoxTextEditColor)
  {
    m_dsBoxTextEditColor = dsBoxTextEditColor;
    emit dsBoxTextEditColorChanged(m_dsBoxTextEditColor);
  }
}

QColor StyleWidget::dsBoxBackgroundReadyColor() const
{
  return m_dsBoxBackgroundReadyColor;
}

void StyleWidget::setdsBoxBackgroundReadyColor(const QColor &dsBoxBackgroundReadyColor)
{
  if(m_dsBoxBackgroundReadyColor != dsBoxBackgroundReadyColor)
  {
    m_dsBoxBackgroundReadyColor = dsBoxBackgroundReadyColor;
    emit dsBoxBackgroundReadyColorChanged(m_dsBoxBackgroundReadyColor);
  }
}

QColor StyleWidget::dsBoxBackgroundErrorColor() const
{
  return m_dsBoxBackgroundErrorColor;
}

void StyleWidget::setdsBoxBackgroundErrorColor(const QColor &dsBoxBackgroundErrorColor)
{
  if(m_dsBoxBackgroundErrorColor != dsBoxBackgroundErrorColor)
  {
    m_dsBoxBackgroundErrorColor = dsBoxBackgroundErrorColor;
    emit dsBoxBackgroundErrorColorChanged(m_dsBoxBackgroundErrorColor);
  }
}

QColor StyleWidget::dsBoxTextDefColor() const
{
  return m_dsBoxTextDefColor;
}

void StyleWidget::setdsBoxTextDefColor(const QColor &dsBoxTextDefColor)
{
  if(m_dsBoxTextDefColor != dsBoxTextDefColor)
  {
    m_dsBoxTextDefColor = dsBoxTextDefColor;
    emit dsBoxTextDefColorChanged(m_dsBoxTextDefColor);
  }
}

