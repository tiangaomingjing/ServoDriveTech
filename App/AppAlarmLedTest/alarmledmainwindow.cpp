#include "alarmledmainwindow.h"
#include "ui_alarmledmainwindow.h"

#include "ledalarm.h"

AlarmLedMainWindow::AlarmLedMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AlarmLedMainWindow)
{
  ui->setupUi(this);
  QMenu *menu=new QMenu(ui->pushButton);
  QAction *act=new QAction("Action1",menu);
  menu->addAction(act);
  act=new QAction("Action2",menu);
  menu->addAction(act);
  ui->pushButton->setToolTip("aaaaaaaaaaaaaa");
//  ui->pushButton->setMenu(menu);

  ui->pushButton_2->setToolTip("bbbbbbbbbbbbbbb");

  led=new LedAlarm("hello",this);
  ui->verticalLayout->addWidget(led);

  act=new QAction("Action3",menu);
  led->addMenuAction(act);
  act=new QAction("Action4",menu);
  led->addMenuAction(act);
}

AlarmLedMainWindow::~AlarmLedMainWindow()
{
  delete ui;
}

void AlarmLedMainWindow::on_pushButton_clicked()
{
//    ui->pushButton->menu()->exec();
  led->setMenuActive(true);
}

void AlarmLedMainWindow::on_pushButton_2_clicked()
{
    led->setMenuActive(false);
}
