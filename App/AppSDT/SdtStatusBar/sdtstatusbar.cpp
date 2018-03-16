#include "sdtstatusbar.h"
#include "ui_sdtstatusbar.h"

#include <QDebug>
#include <QMenu>

#include "gtutils.h"
#include "Option"
#include "appiconname.h"

#include "statuserrdialog.h"


SdtStatusBar::SdtStatusBar(QTreeWidget *navTree, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SdtStatusBar)
{
  ui->setupUi(this);
  m_errDialog=new StatusErrDialog(navTree,this);
  connect(m_errDialog,SIGNAL(statusPageChanged(int)),this,SIGNAL(statusPageChanged(int)));

//  QPalette pa;
//  pa.setColor(QPalette::WindowText,Qt::red);
//  ui->labelMsg->setPalette(pa);
//  ui->tbtnError->setPopupMode(QToolButton::MenuButtonPopup);
  ui->tbtnError->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  ui->tbtnError->setText(tr("Error"));
  ui->tbtnError->setIconSize(QSize(32,32));
  ui->tbtnError->setAutoRaise(true);
  connect(ui->tbtnError,SIGNAL(clicked(bool)),this,SLOT(onActnToolClicked()));
//  connect(ui->tbtnError,SIGNAL(triggered(QAction*)),this,SLOT(onActnToolTrig(QAction*)));

//  m_menu=new QMenu("error");
//  m_menu->installEventFilter(this);
//  QMenu *menu1=new QMenu("error1");
//  QAction *act=new QAction("act1",menu1);
//  QAction *act2=new QAction("act2",menu1);
//  act->setData("SDT");
//  act2->setData("SDT2");
//  menu1->addAction(act);
//  menu1->addAction(act2);
//  QMenu *menu2=new QMenu("error2");
//  m_menu->addMenu(menu1);
//  m_menu->addMenu(menu2);
//  ui->tbtnError->setMenu(m_menu);
  ui->tbtnNet->setAutoRaise(true);

//  resetStatus();
  setConnectStatus(false);
  setErrorStatus(true);
}

SdtStatusBar::~SdtStatusBar()
{
  delete ui;
}

void SdtStatusBar::resetStatus()
{
  ui->labelMsg->setText("");
  ui->progressBar->setValue(0);
  ui->progressBar->setVisible(false);
  ui->tbtnError->setVisible(false);
}

void SdtStatusBar::setMsg(const QString &str,MsgType type)
{
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  StyleWidget *style=face->customStyleWidget();
  int r,g,b;
  QString ss;
  QColor color;
  switch (type)
  {
  case MSG_TYPE_NORMAL:
    color=style->msgNormalColor();
    break;
  case MSG_TYPE_WARNING:
    color=style->msgWarningColor();
    break;
  case MSG_TYPE_ERROR:
    color=style->msgErrorColor();
    break;
  default:
    break;
  }
  FILL_RGB(color,r,g,b);
  ss=QString("QLabel{color:rgb(%1,%2,%3);}").arg(r).arg(g).arg(b);
//  qDebug()<<"setMsg "<<ss;
  ui->labelMsg->setText(str);
  ui->labelMsg->setStyleSheet(ss);
}

void SdtStatusBar::setConnectStatus(bool connected)
{
  QPixmap pix;
  QString path;
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  if(connected)
    path=GTUtils::customPath()+"option/style/"+face->css()+"/icon/"+ICON_STATUS_CONNECT;
  else
    path=GTUtils::customPath()+"option/style/"+face->css()+"/icon/"+ICON_STATUS_DISCONNECT;
  pix.load(path);
  ui->tbtnNet->setIcon(QIcon(path));
}

void SdtStatusBar::setErrorStatus(bool hasError)
{
  if(hasError)
  {
    OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
    QString path=GTUtils::customPath()+"option/style/"+face->css()+"/icon/"+ICON_STATUS_ERROR;
    ui->tbtnError->setIcon(QIcon(path));
//    qDebug()<<"setErrorStatus"<<path;
  }
  ui->tbtnError->setVisible(hasError);
}


//!
//! \brief SdtStatusBar::updateDeviceWhenChanged
//! 当设备变化后要重新调用，并在生成导航树之后
//! \param navTree
//!
void SdtStatusBar::updateDeviceWhenChanged(QTreeWidget *navTree)
{
  m_errDialog->updateDevice(navTree);
}
QProgressBar *SdtStatusBar::statusProgressBar()const
{
  return ui->progressBar;
}

void SdtStatusBar::setAlarmErrorStatus(quint32 devInx, qint16 axis, bool hasErr)
{
  m_errDialog->setStatusError(devInx,axis,hasErr);
//  qDebug()<<"SdtStatusBar::onStatusErr";
}

//bool SdtStatusBar::eventFilter(QObject *watched, QEvent *event)
//{
//  if(watched==m_menu&&event->type()==QEvent::Close)
//    qDebug()<<"menu eventFilter"<<event->type();
//  if(watched==m_menu&&event->type()==QEvent::Show)
//    qDebug()<<"menu eventFilter"<<event->type();
//  return QWidget::eventFilter(watched,event);
//}

//void SdtStatusBar::onActnClickedtest(QAction *act)
//{
//  qDebug()<<"aaaaaaaaaa"<<act->data();
//}

void SdtStatusBar::onActnToolClicked()
{
  qDebug()<<"bbbbbbbbb";
  m_errDialog->show();
}

//void SdtStatusBar::onStatusErr(quint32 devInx, qint16 axis, bool hasErr)
//{
//  m_errDialog->setStatusError(devInx,axis,hasErr);
//  qDebug()<<"SdtStatusBar::onStatusErr";
//}
//void SdtStatusBar::onActnToolTrig(QAction *act)
//{
//  qDebug()<<"aaaaaaaaaa"<<act->data();
//}
