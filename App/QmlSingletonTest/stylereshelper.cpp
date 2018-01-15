#include "stylereshelper.h"

StyleResHelper::StyleResHelper(QObject *parent) : QObject(parent)
{

}

int StyleResHelper::fontSize() const
{
  return m_fontSize;
}

void StyleResHelper::setFontSize(int fontSize)
{
  m_fontSize = fontSize;
}

QString StyleResHelper::language() const
{
  return m_language;
}

void StyleResHelper::setLanguage(const QString &language)
{
  m_language = language;
}

QString StyleResHelper::css() const
{
  return m_css;
}

void StyleResHelper::setCss(const QString &css)
{
  m_css = css;
}

