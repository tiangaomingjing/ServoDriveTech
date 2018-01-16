#include "optionmainwindow.h"
#include "ui_optionmainwindow.h"

#include "dialogoption.h"
#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"

#include "gtutils.h"

#include <QDebug>
#include <QDir>

OptionMainWindow::OptionMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::OptionMainWindow)
{
  ui->setupUi(this);
  QString icopath=GTUtils::iconPath();

  ui->actionOption->setToolTip("aaaaaaaaaaaaaaa");
  ui->actionOption->setStatusTip("bbbbbbbbbbbbbbbbbbbb");
  ui->actionOption->setIcon(QIcon(icopath+"configtree.png"));
//  centralWidget()->hide();
//  QMenu *menu=new QMenu(ui->toolButton);
//  menu->addMenu("0");
//  menu->addMenu("1");
//  menu->addMenu("2");
//  menu->addMenu("3");
//  menu->addMenu("4");
//  menu->addMenu("5");
//  ui->toolButton->setMenu(menu);

  QAction *act=new QAction("0",ui->toolButton);
  ui->toolButton->addAction(act);
  act=new QAction("1",ui->toolButton);
  ui->toolButton->addAction(act);
  act=new QAction("2",ui->toolButton);
  ui->toolButton->addAction(act);
  act=new QAction("3",ui->toolButton);
  ui->toolButton->addAction(act);
  act=new QAction("4",ui->toolButton);
  ui->toolButton->addAction(act);
  ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup);

  QToolButton *tb=new  QToolButton;
  tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  tb->setIcon(QIcon(icopath+"clear.png"));
  tb->setText("tbtn");
  act=new QAction("btn0",tb);
  connect(act,SIGNAL(triggered(bool)),this,SLOT(onToolBtnActionClicked()));
  act->setToolTip("btn00000000000000000000");
  act->setStatusTip("btn0000000000000000000000000000000000000000");
  tb->addAction(act);
  act=new QAction("btn1",tb);
  tb->addAction(act);
  act=new QAction("btn2",tb);
  tb->addAction(act);
  act=new QAction("btn3",tb);
  tb->addAction(act);
  act=new QAction("btn4",tb);
  tb->addAction(act);
  act=new QAction("btn5",tb);
  tb->setToolTip("tttttttttttttttttttttt");
  tb->setStatusTip("ttttttttttttttttttttttttttttt");
  tb->addAction(act);
  tb->setPopupMode(QToolButton::MenuButtonPopup);
  connect(tb,SIGNAL(clicked(bool)),this,SLOT(onToolBtnClicked()));
  ui->mainToolBar->addWidget(tb);
  ui->mainToolBar->setIconSize(QSize(32,32));
  ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

  ui->pushButton->setToolTip("pushpppppppppppppppppppppppppppppppp");
  ui->pushButton->setStatusTip("pddpdddddddddddddddddddddddddd");

  QWidget *titleBar=ui->dockWidget_2->titleBarWidget();
  QWidget *emptyBar=new QWidget();
  ui->dockWidget_2->setTitleBarWidget(emptyBar);
  delete titleBar;


  ui->tbtn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  ui->tbtn2->setIcon(QIcon(icopath+"clear.png"));
  ui->tbtn2->setText("tbtn");
  ui->tbtn2->setIconSize(QSize(32,32));
  act=new QAction("btn0",ui->tbtn2);
  connect(act,SIGNAL(triggered(bool)),this,SLOT(onToolBtnActionClicked()));
  act->setToolTip("btn00000000000000000000");
  act->setStatusTip("btn0000000000000000000000000000000000000000");
  ui->tbtn2->addAction(act);
  act=new QAction("btn1",ui->tbtn2);
  ui->tbtn2->addAction(act);
  act=new QAction("btn2",ui->tbtn2);
  ui->tbtn2->addAction(act);
  act=new QAction("btn3",ui->tbtn2);
  ui->tbtn2->addAction(act);
  act=new QAction("btn4",ui->tbtn2);
  ui->tbtn2->addAction(act);
  act=new QAction("btn5",ui->tbtn2);
  ui->tbtn2->setToolTip("tttttttttttttttttttttt");
  ui->tbtn2->setStatusTip("ttttttttttttttttttttttttttttt");
  ui->tbtn2->addAction(act);
  ui->tbtn2->setPopupMode(QToolButton::MenuButtonPopup);

  QMenu *menu=new QMenu;
  QMenu *menu1=new QMenu("m1",menu);
  QMenu *menu2=new QMenu("m2",menu);
  QMenu *menu3=new QMenu("m3",menu);
  QMenu *menu4=new QMenu("m4",menu);
  QMenu *menu5=new QMenu("m5",menu);
  menu->addMenu(menu1);
  act=new QAction("btn0",menu1);
  connect(act,SIGNAL(triggered(bool)),this,SLOT(onToolBtnActionClicked()));
  act->setToolTip("btn00000000000000000000");
  act->setStatusTip("btn0000000000000000000000000000000000000000");
  menu1->addAction(act);
  menu->addMenu(menu2);
  menu->addMenu(menu3);
  menu->addMenu(menu4);
  menu->addMenu(menu5);
  ui->tbtn_menu->setMenu(menu);
  ui->tbtn_menu->setPopupMode(QToolButton::InstantPopup);

  ui->pushButton_2->addAction(act);
}

OptionMainWindow::~OptionMainWindow()
{
  delete ui;
}

void OptionMainWindow::on_actionOption_triggered()
{
    DialogOption dialogOpt;
    OptContainer *optc=OptContainer::instance();
    foreach (IOpt *opt, optc->optItems())
    {
      opt->uiInit();
    }
    dialogOpt.exec();
}

void OptionMainWindow::onToolBtnClicked()
{
  qDebug()<<"onToolBtnClicked";
}

void OptionMainWindow::onToolBtnActionClicked()
{
  qDebug()<<"onToolBtnActionClicked";
}

void OptionMainWindow::closeEvent(QCloseEvent *e)
{
  OptContainer *optc=OptContainer::instance();
  optc->saveOpt();
  QMainWindow::closeEvent(e);
}
void OptionMainWindow::TEST_getAllFileInOneFolder()
{
  QString langPath=GTUtils::languagePath()+"ch/";
  qDebug()<<"langPath="<<langPath;
  QDir dir(langPath);
//  dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

//  dir.setSorting(QDir::Size | QDir::Reversed);

  QStringList nameFilters,list;
  nameFilters<<"*.qm";
//  list=dir.entryList();
  list=dir.entryList(nameFilters,QDir::Files|QDir::Hidden|QDir::NoSymLinks,QDir::Name);
  qDebug()<<"list count"<<list.count();
  foreach (QString s, list) {
    qDebug()<<s;
  }
}

void OptionMainWindow::on_pushButton_clicked()
{
    TEST_getAllFileInOneFolder();
}
