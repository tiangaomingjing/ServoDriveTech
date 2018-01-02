#include "widgetmainwindow.h"
#include "ui_widgetmainwindow.h"
#include <QToolButton>

WidgetMainWindow::WidgetMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::WidgetMainWindow)
{
  ui->setupUi(this);
  QWidget *spacer=new QWidget(this);
  spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  ui->mainToolBar->addWidget(spacer);
  QToolButton *tbuton=new QToolButton(this);
  tbuton->setText("more");
  QMenu *menu=new QMenu(tbuton);
  QMenu *menu1=new QMenu(tbuton);
  menu1->setTitle("m1");
  QMenu *menu2=new QMenu(tbuton);
  menu2->setTitle("m2");
  QMenu *menu3=new QMenu(tbuton);
  menu3->setTitle("m3");
  QMenu *menu4=new QMenu(tbuton);
  menu4->setTitle("m4");
  menu->addMenu(menu1);
  menu->addMenu(menu2);
  menu->addMenu(menu3);
  menu->addMenu(menu4);
  tbuton->setPopupMode(QToolButton::MenuButtonPopup);
  tbuton->setMenu(menu);
  ui->mainToolBar->addWidget(tbuton);


}

WidgetMainWindow::~WidgetMainWindow()
{
  delete ui;
}
