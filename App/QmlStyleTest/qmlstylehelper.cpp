#include "qmlstylehelper.h"

QmlStyleHelper::QmlStyleHelper(QObject *parent) : QObject(parent)
{

}
QmlStyleHelper::QmlStyleHelper(int fontSize,const QString &lang,const QString &css,QObject *parent):QObject(parent),
  m_fontSize(fontSize),
  m_language(lang),
  m_css(css)
{

}

int QmlStyleHelper::fontSize() const
{
  return m_fontSize;
}

void QmlStyleHelper::setFontSize(int fontSize)
{
  if(m_fontSize!=fontSize)
  {
    m_fontSize = fontSize;
    emit fontSizeChanged(fontSize);
  }
}

QString QmlStyleHelper::language() const
{
  return m_language;
}

void QmlStyleHelper::setLanguage(const QString &language)
{
  if(m_language!=language)
  {
    m_language = language;
    emit languageChanged(language);
  }

}

QString QmlStyleHelper::css() const
{
  return m_css;
}

void QmlStyleHelper::setCss(const QString &css)
{
  if(m_css!=css)
  {
    m_css = css;
    emit cssChanged(css);
  }

}

