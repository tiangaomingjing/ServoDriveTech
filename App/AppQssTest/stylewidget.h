#ifndef STYLEWIDGET_H
#define STYLEWIDGET_H

#include <QWidget>

//must be inherit from QWidget
class StyleWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor dsBoxBackgroundDefColor READ dsBoxBackgroundDefColor WRITE setdsBoxBackgroundDefColor NOTIFY dsBoxBackgroundDefColorChanged)
  Q_PROPERTY(QColor dsBoxBackgroundReadyColor READ dsBoxBackgroundReadyColor WRITE setdsBoxBackgroundReadyColor NOTIFY dsBoxBackgroundReadyColorChanged)
  Q_PROPERTY(QColor dsBoxBackgroundErrorColor READ dsBoxBackgroundErrorColor WRITE setdsBoxBackgroundErrorColor NOTIFY dsBoxBackgroundErrorColorChanged)
  Q_PROPERTY(QColor dsBoxTextEditColor READ dsBoxTextEditColor WRITE setdsBoxTextEditColor NOTIFY dsBoxTextEditColorChanged)
  Q_PROPERTY(QColor dsBoxTextDefColor READ dsBoxTextDefColor WRITE setdsBoxTextDefColor NOTIFY dsBoxTextDefColorChanged)

  Q_PROPERTY(QColor msgNormalColor READ msgNormalColor WRITE setMsgNormalColor NOTIFY msgNormalColorChanged)
  Q_PROPERTY(QColor msgWarningColor READ msgWarningColor WRITE setMsgWarningColor NOTIFY msgWarningColorChanged)
  Q_PROPERTY(QColor msgErrorColor READ msgErrorColor WRITE setMsgErrorColor NOTIFY msgErrorColorChanged)
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

  QColor msgNormalColor() const;
  void setMsgNormalColor(const QColor &msgNormalColor);

  QColor msgWarningColor() const;
  void setMsgWarningColor(const QColor &msgWarningColor);

  QColor msgErrorColor() const;
  void setMsgErrorColor(const QColor &msgErrorColor);

signals:
  void dsBoxBackgroundDefColorChanged(QColor &clr);
  void dsBoxTextEditColorChanged(QColor &clr);
  void dsBoxBackgroundReadyColorChanged(QColor &clr);
  void dsBoxBackgroundErrorColorChanged(QColor &clr);
  void dsBoxTextDefColorChanged(QColor &clr);
  void msgNormalColorChanged(QColor &clr);
  void msgWarningColorChanged(QColor &clr);
  void msgErrorColorChanged(QColor &clr);

public slots:
private:
  QColor m_dsBoxBackgroundDefColor;
  QColor m_dsBoxBackgroundReadyColor;
  QColor m_dsBoxBackgroundErrorColor;
  QColor m_dsBoxTextDefColor;
  QColor m_dsBoxTextEditColor;

  QColor m_msgNormalColor;
  QColor m_msgWarningColor;
  QColor m_msgErrorColor;
};

#endif // STYLEWIDGET_H
