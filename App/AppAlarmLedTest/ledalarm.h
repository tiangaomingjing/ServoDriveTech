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

  explicit LedAlarm(const QString &name,QWidget *parent = 0, quint16 id=0,LedTextPosition pos = LED_TEXT_LEFT);
  ~LedAlarm();
  void setLedName(const QString &name);
  void addMenuAction(QAction *action);

  bool menuActive() const;
  void setMenuActive(bool active);

signals:

public slots:
private:
  class Led;
  Led *m_led;
  QLabel *m_label;
  quint16 m_id;
  QMenu *m_menu;
  bool m_menuActive;
};

class LedAlarm::Led:public QPushButton
{
  Q_OBJECT
public:
  explicit Led(LedAlarm *parent=0);
  ~Led();
private slots:
  void onBtnClicked();
private:
  QMenu *m_menu;
  LedAlarm *m_parent;
};

#endif // LEDALARM_H
