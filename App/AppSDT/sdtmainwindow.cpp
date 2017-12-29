#include "sdtmainwindow.h"
#include "ui_sdtmainwindow.h"

#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"

#include "gtutils.h"
#include "appiconname.h"

SDTMainWindow::SDTMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SDTMainWindow)
{
  ui->setupUi(this);
  staticUiInit();
}

SDTMainWindow::~SDTMainWindow()
{
  delete ui;
}

void SDTMainWindow::staticUiInit()
{
  toolBarOwnInit();
  ui->btnNew->setVisible(false);

  createActions();
  setAppIcon();

}
void SDTMainWindow::toolBarOwnInit()
{
  QWidget *titleBar=ui->dockWidgetToolBar->titleBarWidget();
  QWidget *emptyBar=new QWidget();
  ui->dockWidgetToolBar->setTitleBarWidget(emptyBar);
  delete titleBar;
}
void SDTMainWindow::createActions()
{
//  ui->tbtnDisconnect->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//  ui->tbtnDisconnect->setText(tr("disnet"));
//  ui->tbtnDisconnect->setIconSize(QSize(32,32));
//  m_actnDisNet=new QAction(this);
//  m_actnDisNet->setText(tr("disnet"));
//  ui->tbtnDisconnect->addAction(m_actnDisNet);
//  m_actnDisMode=new QAction(this);
//  m_actnDisMode->setText(tr("dismode"));
//  ui->tbtnDisconnect->addAction(m_actnDisMode);
////  connect(act,SIGNAL(triggered(bool)),this,SLOT(onToolBtnActionClicked()));
//  ui->tbtnDisconnect->setPopupMode(QToolButton::MenuButtonPopup);
}

void SDTMainWindow::setAppIcon()
{
//  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
//  QString iconPath=GTUtils::customPath()+"/option/style/"+face->css()+"/icon/";
//  ui->tbtnDisconnect->setIcon(QIcon(iconPath+ICON_DISNET));
//  m_actnDisNet->setIcon(QIcon(iconPath+ICON_DISNET));
//  m_actnDisMode->setIcon(QIcon(iconPath+ICON_OFFLINEMODE));
}
