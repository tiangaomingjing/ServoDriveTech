#ifndef QMLSTYLEHELPER_H
#define QMLSTYLEHELPER_H

#include <QObject>
#include "option_global.h"

class OPTIONSHARED_EXPORT QmlStyleHelper : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
  Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
  Q_PROPERTY(QString css READ css WRITE setCss NOTIFY cssChanged)
public:
  explicit QmlStyleHelper(QObject *parent = 0);
  explicit QmlStyleHelper(int fontSize,const QString &lang,const QString &css,QObject *parent = 0);

  int fontSize() const;
  void setFontSize(int fontSize);

  QString language() const;
  void setLanguage(const QString &language);

  QString css() const;
  void setCss(const QString &css);

signals:
  void fontSizeChanged(int size);
  void languageChanged(QString lang);
  void cssChanged(QString css);

public slots:
private:
  int m_fontSize;
  QString m_language;
  QString m_css;
};

#endif // QMLSTYLEHELPER_H
