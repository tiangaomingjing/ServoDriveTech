#ifndef IGRAPHSTATUS_H
#define IGRAPHSTATUS_H

#include <QWidget>
#include "iuiwidget_global.h"
#include "igraph.h"
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
  void setError(bool error);

signals:

public slots:
private:
  class Led;
  Led *m_led;
  QLabel *m_label;
  quint16 m_id;
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


class IGraphStatusPrivate;
class IUiWidget;
class IUIWIDGETSHARED_EXPORT IGraphStatus : public IGraph
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphStatus)
public:
//  explicit IGraphStatus(QWidget *parent = 0);
  virtual ~IGraphStatus();
  void visit(IUiWidget *uiWidget) Q_DECL_OVERRIDE;

protected:
  virtual void setUiVersionName()Q_DECL_OVERRIDE =0;
  virtual void setCustomVisitActive(IUiWidget*uiWidget);
  virtual void setupDataMappings()=0;

  virtual void setDeviceStatusIconByCss(const QString &css)=0;
  virtual QWidget *alarmBackgroundWidget()=0;

signals:

public slots:

protected slots:
  virtual void onFaceCssChanged(const QString &css);
protected:
  IGraphStatus(IGraphStatusPrivate&dd, QWidget *parent=0);

};

#endif // IGRAPHSTATUS_H
