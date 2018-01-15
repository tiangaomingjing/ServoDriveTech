#ifndef STYLERESHELPER_H
#define STYLERESHELPER_H

#include <QObject>

class StyleResHelper : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize)
  Q_PROPERTY(QString language READ language WRITE setLanguage)
  Q_PROPERTY(QString css READ css WRITE setCss)

public:
  explicit StyleResHelper(QObject *parent = 0);

  Q_INVOKABLE int fontSize() const;
  Q_INVOKABLE void setFontSize(int fontSize);

  Q_INVOKABLE QString language() const;
  Q_INVOKABLE void setLanguage(const QString &language);

  Q_INVOKABLE QString css() const;
  Q_INVOKABLE void setCss(const QString &css);

signals:

public slots:
private:
  int m_fontSize;
  QString m_language;
  QString m_css;

};

#endif // STYLERESHELPER_H
