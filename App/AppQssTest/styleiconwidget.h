#ifndef STYLEICONWIDGET
#define STYLEICONWIDGET

#include <QVBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QObject>
#include <QPainter>
#include <QDebug>

class StyleIconWidget:public QWidget
{
  Q_OBJECT
public:
  explicit StyleIconWidget(const QString &iconpath,const QString &title,const QString &css,QWidget *parent):QWidget(parent),
    m_css(css)
  {
    QVBoxLayout *vlayout=new QVBoxLayout(this);
    m_icon=new QLabel(this);
    m_icon->setPixmap(QPixmap(iconpath));
    m_icon->setAlignment(Qt::AlignCenter);
    m_title=new QLabel(this);
    m_title->setText(title);
    m_title->setAlignment(Qt::AlignCenter);
    vlayout->addWidget(m_icon);
    vlayout->addWidget(m_title);
    vlayout->setStretch(0,1);
    vlayout->setStretch(1,0);
    QString s="StyleIconWidget:hover{\
        border: 2px solid red;\
        border-radius:5px;\
      }";
    setStyleSheet(s);
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
    m_title->setText(text);
  }

signals:
  void cssChanged(QString css);
protected:

  void mouseReleaseEvent(QMouseEvent *)
  {
    emit cssChanged(m_css);
    qDebug()<<"emit css changed"<<m_css;
    m_pressed=true;
    update();
  }

  void paintEvent(QPaintEvent *event)
  {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    if(m_pressed)
    {
      QRect rect;
      rect=this->rect();
      p.fillRect(rect,Qt::gray);
      m_pressed=false;
    }
    QWidget::paintEvent(event);
  }

private:
  QLabel *m_icon;
  QLabel *m_title;
  QString m_css;
  bool m_pressed;

};
#endif // STYLEICONWIDGET

