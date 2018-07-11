#include "stylewidget.h"

StyleWidget::StyleWidget(QWidget *parent) : QWidget(parent),
  m_dsBoxBackgroundDefColor(Qt::white),
  m_dsBoxBackgroundReadyColor(Qt::yellow),
  m_dsBoxBackgroundErrorColor(Qt::red),
  m_dsBoxTextDefColor(Qt::black),
  m_dsBoxTextEditColor(Qt::red),
  m_msgNormalColor(Qt::black),
  m_msgWarningColor(Qt::yellow),
  m_msgErrorColor(Qt::red)
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

QColor StyleWidget::msgNormalColor() const
{
  return m_msgNormalColor;
}

void StyleWidget::setMsgNormalColor(const QColor &msgNormalColor)
{
  if(m_msgNormalColor != msgNormalColor)
  {
    m_msgNormalColor = msgNormalColor;
    emit msgNormalColorChanged(m_msgNormalColor);
  }
}

QColor StyleWidget::msgWarningColor() const
{
  return m_msgWarningColor;
}

void StyleWidget::setMsgWarningColor(const QColor &msgWarningColor)
{
  if(m_msgWarningColor != msgWarningColor)
  {
    m_msgWarningColor = msgWarningColor;
    emit msgWarningColorChanged(m_msgWarningColor);
  }
}

QColor StyleWidget::msgErrorColor() const
{
  return m_msgErrorColor;
}

void StyleWidget::setMsgErrorColor(const QColor &msgErrorColor)
{
  if(m_msgErrorColor != msgErrorColor)
  {
    m_msgErrorColor = msgErrorColor;
    emit msgErrorColorChanged(m_msgErrorColor);
  }
}

