#ifndef STYLEWIDGET_H
#define STYLEWIDGET_H

#include <QWidget>

class StyleWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor dsBoxBackgroundDefColor READ dsBoxBackgroundDefColor WRITE setdsBoxBackgroundDefColor NOTIFY dsBoxBackgroundDefColorChanged)
  Q_PROPERTY(QColor dsBoxBackgroundReadyColor READ dsBoxBackgroundReadyColor WRITE setdsBoxBackgroundReadyColor NOTIFY dsBoxBackgroundReadyColorChanged)
  Q_PROPERTY(QColor dsBoxBackgroundErrorColor READ dsBoxBackgroundErrorColor WRITE setdsBoxBackgroundErrorColor NOTIFY dsBoxBackgroundErrorColorChanged)
  Q_PROPERTY(QColor dsBoxTextEditColor READ dsBoxTextEditColor WRITE setdsBoxTextEditColor NOTIFY dsBoxTextEditColorChanged)
  Q_PROPERTY(QColor dsBoxTextDefColor READ dsBoxTextDefColor WRITE setdsBoxTextDefColor NOTIFY dsBoxTextDefColorChanged)
public:
  explicit StyleWidget(QWidget *parent = 0);

  QColor dsBoxBackgroundDefColor() const;
  void setdsBoxBackgroundDefColor(const QColor &dsBoxBackgroundDefColor);

  QColor dsBoxTextEditColor() const;
  void setdsBoxTextEditColor(const QColor &dsBoxTextEditColor);

  QColor dsBoxBackgroundReadyColor() const;
  void setdsBoxBackgroundReadyColor(const QColor &dsBoxBackgroundReadyColor);

  QColor dsBoxBackgroundErrorColor() const;
  void setdsBoxBackgroundErrorColor(const QColor &dsBoxBackgroundErrorColor);

  QColor dsBoxTextDefColor() const;
  void setdsBoxTextDefColor(const QColor &dsBoxTextDefColor);

signals:
  void dsBoxBackgroundDefColorChanged(QColor &clr);
  void dsBoxTextEditColorChanged(QColor &clr);
  void dsBoxBackgroundReadyColorChanged(QColor &clr);
  void dsBoxBackgroundErrorColorChanged(QColor &clr);
  void dsBoxTextDefColorChanged(QColor &clr);

public slots:
private:
  QColor m_dsBoxBackgroundDefColor;
  QColor m_dsBoxBackgroundReadyColor;
  QColor m_dsBoxBackgroundErrorColor;

  QColor m_dsBoxTextDefColor;
  QColor m_dsBoxTextEditColor;
};

#endif // STYLEWIDGET_H
