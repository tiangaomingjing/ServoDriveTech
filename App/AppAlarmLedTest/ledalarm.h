#ifndef LEDALARM_H
#define LEDALARM_H

#include <QWidget>
#include <QPushButton>
class QAction;
class QMenu;
class QLabel;

class LedAlarm : public QWidget
{
  Q_OBJECT
public:
  enum LedTextPosition{
    LED_TEXT_LEFT,
    LED_TEXT_BOTTOM
  };

  explicit LedAlarm(const QString &name,QWidget *parent = 0, qint16 id=0,LedTextPosition pos = LED_TEXT_LEFT);
  ~LedAlarm();
  void setLedName(const QString &name);
  void addMenuAction(QAction *action);

  bool menuActive() const;
  void setMenuActive(bool active);
  void setError(bool error);
  qint16 id() const;

signals:

public slots:
private:
  class Led;
  Led *m_led;
  QLabel *m_label;
  qint16 m_id;
  bool m_menuActive;
};

class LedAlarm::Led:public QPushButton
{
  Q_OBJECT
  Q_PROPERTY(QColor passColor READ passColor WRITE setPassColor NOTIFY passColorChanged)
  Q_PROPERTY(QColor errorColor READ errorColor WRITE setErrorColor NOTIFY errorColorChanged)
public:
  explicit Led(LedAlarm *parent=0);
  ~Led();

  QSize sizeHint() const Q_DECL_OVERRIDE;

  QColor passColor() const;
  void setPassColor(const QColor &passColor);

  QColor errorColor() const;
  void setErrorColor(const QColor &errorColor);

  bool hasError() const;
  void setError(bool error);

protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:
  void passColorChanged(const QColor &color);
  void errorColorChanged(const QColor &color);

private:
  QMenu *m_menu;
  LedAlarm *m_parent;
  QColor m_passColor;
  QColor m_errorColor;
  bool m_hasError;
};

#endif // LEDALARM_H
