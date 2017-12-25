#ifndef STYLEICONWIDGET
#define STYLEICONWIDGET

#include <QVBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QObject>
#include <QPainter>

class StyleIconWidget:public QWidget
{
  Q_OBJECT
  Q_PROPERTY(bool pressed READ isPressed WRITE setPressed NOTIFY pressed)
public:
  explicit StyleIconWidget(const QString &iconpath,const QString &text,QWidget *parent):QWidget(parent)
  {
    QVBoxLayout *vlayout=new QVBoxLayout(this);
    m_icon=new QLabel(this);
    m_icon->setPixmap(QPixmap(iconpath));
    m_icon->setAlignment(Qt::AlignCenter);
    m_text=new QLabel(this);
    m_text->setText(text);
    m_text->setAlignment(Qt::AlignCenter);
    vlayout->addWidget(m_icon);
    vlayout->addWidget(m_text);
    vlayout->setStretch(0,1);
    vlayout->setStretch(1,0);
    QString s="StyleIconWidget:hover:!pressed{\
        border: 2px solid red;\
        border-radius:5px;\
      }\
      StyleIconWidget:hover:pressed{\
        border: 2px solid red;\
        border-radius:5px;\
        background:blue;\
      }";
    setStyleSheet(s);
    update();
  }

  ~StyleIconWidget()
  {

  }
  void setIcon(const QString &iconpath )
  {
    m_icon->setPixmap(QPixmap(iconpath));
  }
  void setIconText(const QString &text)
  {
    m_text->setText(text);
  }

  bool isPressed()
  {
    return m_pressed;
  }
  void setPressed(bool press)
  {
    m_pressed=press;
  }

signals:
  void pressed();
protected:

  void mousePressEvent(QMouseEvent *)
  {
    m_pressed=true;
    emit pressed();
  }
  void mouseReleaseEvent(QMouseEvent *)
  {
    m_pressed=false;
  }

  void paintEvent(QPaintEvent *event)
  {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
  }

private:
  QLabel *m_icon;
  QLabel *m_text;
  bool m_pressed;

};
#endif // STYLEICONWIDGET

