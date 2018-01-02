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

#include "dialogoption.h"

#include <QToolButton>
#include <QDebug>

SDTMainWindow::SDTMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SDTMainWindow)
{
  ui->setupUi(this);
  staticUiInit();
  showMaximized();
}

SDTMainWindow::~SDTMainWindow()
{
  delete ui;
}

void SDTMainWindow::staticUiInit()
{
  createActions();
  setAppIcon();

  OptAutoLoad *optAuto=dynamic_cast<OptAutoLoad *>(OptContainer::instance()->optItem("optautoload"));
  if(optAuto!=NULL)
  {
    connect(optAuto,SIGNAL(autoLoadChanged(bool)),this,SLOT(onOptAutoLoadChanged(bool)));
    m_actnNewConfig->setVisible(!optAuto->autoLoad());
  }
  OptFace *optface=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  if(optface!=NULL)
    connect(optface,SIGNAL(faceCssChanged(QString)),this,SLOT(onOptFaceCssChanged(QString)));

}
void SDTMainWindow::createActions()
{
  ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  ui->mainToolBar->setIconSize(QSize(32,32));
  m_actnConnect=new QAction(this);
  m_actnConnect->setText(tr("connet"));

  m_actnDisNet=new QAction(this);
  m_actnDisNet->setText(tr("disnet"));

  m_actnNewConfig=new QAction(this);
  m_actnNewConfig->setText(tr("new"));

  m_actnDownload=new QAction(this);
  m_actnDownload->setText(tr("dwnload"));

  m_actnUpload=new QAction(this);
  m_actnUpload->setText(tr("upload"));

  m_actnCompare=new QAction(this);
  m_actnCompare->setText(tr("compare"));

  m_actnConfig=new QAction(this);
  m_actnConfig->setText(tr("config"));

  m_actnSave=new QAction(this);
  m_actnSave->setText(tr("save"));

  QWidget *spacer=new QWidget(this);
  spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  m_tbtnHelp=new QToolButton(this);
  m_tbtnHelp->setPopupMode(QToolButton::MenuButtonPopup);
  m_tbtnHelp->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  m_tbtnHelp->setText(tr("help"));
  m_actnAboutHardware=new QAction(this);
  m_actnAboutHardware->setText(tr("hinfo"));
  m_actnAboutSoftware=new QAction(this);
  m_actnAboutSoftware->setText(tr("sinfo"));
  m_tbtnHelp->addAction(m_actnAboutHardware);
  m_tbtnHelp->addAction(m_actnAboutSoftware);


  //----------------more toolbutton----------------------------
  m_tbtnMore=new QToolButton(this);
//  m_tbtnMore->setToolButtonStyle(Qt::ToolButtonIconOnly);
  m_tbtnMore->setPopupMode(QToolButton::MenuButtonPopup);
//  m_tbtnMore->setPopupMode(QToolButton::InstantPopup);

  m_actnOnMode=new QAction(m_tbtnMore);
  m_actnOnMode->setText(tr("online"));
  m_actnOnMode->setCheckable(true);

  m_actnOffMode=new QAction(m_tbtnMore);
  m_actnOffMode->setText(tr("offline"));
  m_actnOffMode->setCheckable(true);

  QActionGroup *modeGroup=new QActionGroup(m_tbtnMore);
  m_actnOnMode->setChecked(true);
  modeGroup->addAction(m_actnOffMode);
  modeGroup->addAction(m_actnOnMode);

  m_actnUpdateFlash=new QAction(tr("update"),m_tbtnMore);
  m_actnReset=new QAction(tr("rstdsp"),m_tbtnMore);

  m_actnOption=new QAction(tr("option"),m_tbtnMore);
  m_actnProduce=new QAction(tr("produce"),m_tbtnMore);

//  m_tbtnMore->addAction(m_actnOnMode);
//  m_tbtnMore->addAction(m_actnOffMode);
//  m_tbtnMore->addAction(actspacer1);
//  m_tbtnMore->addAction(act1);
//  m_tbtnMore->addAction(act2);
//  m_tbtnMore->addAction(act3);
//  m_tbtnMore->addAction(act4);
//  m_tbtnMore->addAction(act5);
  QMenu *menu=new QMenu(m_tbtnMore);//menu action 不能共存
  QMenu *menuUpdateFlash=new QMenu(tr("UpdateFirmware"),menu);
  QMenu *menuSoftMode=new QMenu(tr("softmode"),menu);

  menu->addMenu(menuUpdateFlash);
  menuUpdateFlash->addAction(m_actnUpdateFlash);
  menuUpdateFlash->addAction(m_actnReset);
  menu->addAction(m_actnOption);
  menu->addAction(m_actnProduce);
  menu->addMenu(menuSoftMode);
  menuSoftMode->addAction(m_actnOnMode);
  menuSoftMode->addAction(m_actnOffMode);
  m_tbtnMore->setMenu(menu);

  //按顺序增加
  ui->mainToolBar->addAction(m_actnConnect);
  ui->mainToolBar->addAction(m_actnDisNet);
  ui->mainToolBar->addAction(m_actnNewConfig);
  ui->mainToolBar->addAction(m_actnDownload);
  ui->mainToolBar->addAction(m_actnUpload);
  ui->mainToolBar->addAction(m_actnCompare);
  ui->mainToolBar->addAction(m_actnConfig);
  ui->mainToolBar->addAction(m_actnSave);
  ui->mainToolBar->addWidget(m_tbtnHelp);
  ui->mainToolBar->addWidget(spacer);
  ui->mainToolBar->addWidget(m_tbtnMore);

  //创建连接slots
  connect(m_actnOption,SIGNAL(triggered(bool)),this,SLOT(onActnOptionClicked()));

}

void SDTMainWindow::setAppIcon()
{
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QString iconPath=GTUtils::customPath()+"/option/style/"+face->css()+"/icon/";
  m_actnConnect->setIcon(QIcon(iconPath+ICON_CONNECT));
  m_actnDisNet->setIcon(QIcon(iconPath+ICON_DISNET));
  m_actnNewConfig->setIcon(QIcon(iconPath+ICON_NEWCONFIG));
  m_actnDownload->setIcon(QIcon(iconPath+ICON_DOWNLOAD));
  m_actnUpload->setIcon(QIcon(iconPath+ICON_UPLOAD));
  m_actnCompare->setIcon(QIcon(iconPath+ICON_COMPARE));
  m_actnConfig->setIcon(QIcon(iconPath+ICON_CONFIG));
  m_actnSave->setIcon(QIcon(iconPath+ICON_SAVE));

  m_tbtnHelp->setIcon(QIcon(iconPath+ICON_HELP));
  m_tbtnMore->setIcon(QIcon(iconPath+ICON_MORE));
}

void SDTMainWindow::closeEvent(QCloseEvent *e)
{
  OptContainer *optc=OptContainer::instance();
  optc->saveOpt();
  QMainWindow::closeEvent(e);
}
void SDTMainWindow::onActnOptionClicked()
{
  DialogOption dialogOpt;
  OptContainer *optc=OptContainer::instance();
  foreach (IOpt *opt, optc->optItems())
  {
    opt->uiInit();
  }
  dialogOpt.exec();
}
void SDTMainWindow::onOptAutoLoadChanged(bool changed)
{
  m_actnNewConfig->setVisible(!changed);
  qDebug()<<"m_actnNewConfig->setVisible"<<!changed;
}
void SDTMainWindow::onOptFaceCssChanged(QString css)
{
  setAppIcon();
  qDebug()<<"setAppIcon"<<css;
}
