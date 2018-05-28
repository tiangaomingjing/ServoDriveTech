#include "alarmledmainwindow.h"
#include "ui_alarmledmainwindow.h"

#include "ledalarm.h"
#include "qflowlayout.h"

#include "qttreemanager.h"
#include <QTreeWidget>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QGridLayout>


AlarmLedMainWindow::AlarmLedMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AlarmLedMainWindow)
{
  ui->setupUi(this);
  setStyleSheet("background-color:#E0DDDD");

  QMenu *menu=new QMenu(ui->pushButton);
  QAction *act=new QAction("Action1",menu);
  menu->addAction(act);
  act=new QAction("Action2",menu);
  menu->addAction(act);

  QString path="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/build/debug/sysconfig/SD6x/SD61_PLUS/V129/PrmFuncDeviceStatusAlarmInfo.xml";
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(path);


  ui->pushButton->setToolTip(tr("cause:\n%1\nsolution:\n%2 ").arg(tree->topLevelItem(0)->child(0)->text(2)).arg(tree->topLevelItem(0)->child(0)->text(3)));
//  ui->pushButton->setMenu(menu);

  ui->pushButton_2->setToolTip("bbbbbbbbbbbbbbb");

  QGridLayout *gridLayout=new QGridLayout;
  gridLayout->setContentsMargins(50,0,0,0);

  QTreeWidgetItem *alarmItem=tree->topLevelItem(0);

  int count=alarmItem->childCount();

  int col=4;
  int row=count/col;
  int remain=count%col;
  int rsv=0;
  if(remain>0)
  {
    row++;
    rsv=col-remain;
  }
  qDebug()<<tr("col=%1 row=%2 rsv=%3").arg(col).arg(row).arg(rsv);

  int rowInx=0;
  int colInx=0;
  QTreeWidgetItem *item=NULL;
  QAction *action=NULL;
  for(int i=0;i<alarmItem->childCount();i++)
  {
    item=alarmItem->child(i);
    led=new LedAlarm(tr("%1").arg(item->text(1)),this,i);

    qDebug()<<"addwidget"<<"row"<<rowInx<<"col"<<colInx<<"count"<<i;
    gridLayout->addWidget(led,rowInx,colInx);
    rowInx++;
    if(rowInx>=row)
    {
      rowInx=0;
      colInx++;
    }
  }

  for(int k=0;k<rsv;k++)
  {
    led=new LedAlarm(tr("hello %1").arg(rowInx),this,-1);

    gridLayout->addWidget(led,rowInx,colInx);
    rowInx++;
  }

    ui->verticalLayout->addLayout(gridLayout);

/***********************
  int count=31;

  int col=4;
//  if(count>24)
//    col=4;
  int row=count/col;
  int remain=count%col;
  int rsv=0;
  if(remain>0)
  {
    row++;
    rsv=col-remain;
  }
  qDebug()<<tr("col=%1 row=%2 rsv=%3").arg(col).arg(row).arg(rsv);

  int addCount=0;
  int i=0;
  int j=0;
  for(i=0;i<col;i++)
  {
    for(j=0;j<row;j++)
    {

      led=new LedAlarm(tr("hello %1").arg(addCount),this,i);
      act=new QAction("Action3",menu);
      led->addMenuAction(act);
      act=new QAction("Action4",menu);
      led->addMenuAction(act);

      qDebug()<<"addwidget"<<"row"<<j<<"col"<<i<<"addCount"<<addCount;
      gridLayout->addWidget(led,j,i);
      addCount++;
      if(addCount>=count)
        break;

    }
  }

  i--;
  j++;
  for(int k=0;k<rsv;k++)
  {
    led=new LedAlarm(tr("hello %1").arg(i),this,i);
    act=new QAction("Action3",menu);
    led->addMenuAction(act);
    act=new QAction("Action4",menu);
    led->addMenuAction(act);

    gridLayout->addWidget(led,j+k,i);
  }
  ui->verticalLayout->addLayout(gridLayout);

********************************/


//  QFlowLayout *flayout=new QFlowLayout;
//  ui->verticalLayout->addLayout(flayout);

//  for(int i=0;i<23;i++){
//    led=new LedAlarm(tr("hello %1").arg(i),this,i);
//    flayout->addWidget(led);


//    act=new QAction("Action3",menu);
//    led->addMenuAction(act);
//    act=new QAction("Action4",menu);
//    led->addMenuAction(act);
//  }

    LedAlarm *alarm=new LedAlarm("test flag",0,-1,LedAlarm::LED_TEXT_BOTTOM);
    alarm->show();
}

AlarmLedMainWindow::~AlarmLedMainWindow()
{
  delete ui;
}

void AlarmLedMainWindow::on_pushButton_clicked()
{
//    ui->pushButton->menu()->exec();
//  led->setMenuActive(true);
  led->setError(true);
}

void AlarmLedMainWindow::on_pushButton_2_clicked()
{
//    led->setMenuActive(false);
    led->setError(false);
}
