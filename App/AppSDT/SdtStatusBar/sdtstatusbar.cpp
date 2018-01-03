#include "sdtstatusbar.h"
#include "ui_sdtstatusbar.h"

#include <QDebug>
#include <QMenu>

SdtStatusBar::SdtStatusBar(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SdtStatusBar)
{
  ui->setupUi(this);
  QPalette pa;
  pa.setColor(QPalette::WindowText,Qt::red);
  ui->labelMsg->setPalette(pa);
  ui->tbtnError->setPopupMode(QToolButton::MenuButtonPopup);
  ui->tbtnError->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  ui->tbtnError->setText(tr("Error"));
  connect(ui->tbtnError,SIGNAL(clicked(bool)),this,SLOT(onActnToolClicked()));
  connect(ui->tbtnError,SIGNAL(triggered(QAction*)),this,SLOT(onActnToolTrig(QAction*)));

  m_menu=new QMenu("error");
  m_menu->installEventFilter(this);
  QMenu *menu1=new QMenu("error1");
  QAction *act=new QAction("act1",menu1);
  QAction *act2=new QAction("act2",menu1);
  act->setData("SDT");
  act2->setData("SDT2");
  menu1->addAction(act);
  menu1->addAction(act2);
  QMenu *menu2=new QMenu("error2");
  m_menu->addMenu(menu1);
  m_menu->addMenu(menu2);
  ui->tbtnError->setMenu(m_menu);

//  resetStatus();
}

SdtStatusBar::~SdtStatusBar()
{
  delete ui;
}

void SdtStatusBar::resetStatus()
{
  ui->labelMsg->setText("");
  ui->progressBar->setValue(0);
  ui->labelMsg->hide();
  ui->progressBar->hide();
  ui->tbtnError->hide();
}

void SdtStatusBar::setWarningMsg(const QString &str)
{
  ui->labelMsg->setText(str);

}

bool SdtStatusBar::eventFilter(QObject *watched, QEvent *event)
{
  if(watched==m_menu&&event->type()==QEvent::Close)
    qDebug()<<"menu eventFilter"<<event->type();
  if(watched==m_menu&&event->type()==QEvent::Show)
    qDebug()<<"menu eventFilter"<<event->type();
  return QWidget::eventFilter(watched,event);
}

void SdtStatusBar::onActnClickedtest(QAction *act)
{
  qDebug()<<"aaaaaaaaaa"<<act->data();
}

void SdtStatusBar::onActnToolClicked()
{
  qDebug()<<"bbbbbbbbb";
}
void SdtStatusBar::onActnToolTrig(QAction *act)
{
  qDebug()<<"aaaaaaaaaa"<<act->data();
}
