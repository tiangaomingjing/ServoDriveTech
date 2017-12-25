#include "optface.h"
#include "ui_optface.h"
#include "iopt_p.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QVBoxLayout>
#include <QLabel>

class StyleIconWidget:public QWidget
{
public:
  explicit StyleIconWidget(const QString &iconpath,const QString &text,QWidget *parent):QWidget(parent)
  {
    QVBoxLayout *vlayout=new QVBoxLayout(this);
    m_icon=new QLabel(this);
    m_icon->setPixmap(QPixmap(iconpath));
    m_text=new QLabel(this);
    m_text->setText(text);
    vlayout->addWidget(m_icon);
    vlayout->addWidget(m_text);
    vlayout->setStretch(0,1);
    vlayout->setStretch(1,0);
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
private:
  QLabel *m_icon;
  QLabel *m_text;

};

class OptFacePrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptFace)
public:
  OptFacePrivate();
  ~OptFacePrivate();
  QString m_css;
  QString m_fontSize;

};
OptFacePrivate::OptFacePrivate()
{

}
OptFacePrivate::~OptFacePrivate()
{

}

OptFace::OptFace(const QString &optName, QWidget *parent) :  IOpt(optName,*new OptFacePrivate,parent),
  ui(new Ui::OptFace)
{
  ui->setupUi(this);
}
OptFace::~OptFace()
{
  delete ui;
}
bool OptFace::optActive()
{
  //这里面的动作都是立即生效的，所以Ui操作之后就执行了
  return true;
}

void OptFace::setFaceStyle(const QString &css)
{
  Q_D(OptFace);
  d->m_css=css;

  QString filename=d->m_optPath+css;

  qDebug()<<filename;
  QFile file(filename);
  if(!file.open(QFile::ReadOnly))
  {
    QTextStream in(&file);

    QString qss = in.readAll();
    qApp->setStyleSheet(qss);
    file.close();
  }
  else
    qDebug()<<"open file :"<<filename<<"error";
}

void OptFace::setFaceFontSize(int size)
{
  Q_D(OptFace);
  d->m_fontSize=size;
  QFont font=qApp->font();
  font.setPixelSize(size);
  qApp->setFont(font);
}
