#include "igraphstatus.h"
#include "igraphstatus_p.h"
#include "ledalarm.h"
#include "qttreemanager.h"
#include "sevdevice.h"
#include "iuiwidget.h"
#include "Option"
#include "sdtglobaldef.h"

#include <QGridLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QLabel>
#include <QAction>
#include <QVBoxLayout>
#include <QTimer>

#define UI_LAYOUT_LED_ALARM_COL 3
#define ALM_DETAIL_FILE_NAME "PrmFuncDeviceStatusAlarmInfo"

#define TIMER_INTERVAL 500


//IGraphStatus::IGraphStatus(QWidget *parent) : IGraph(*(new IGraphStatusPrivate),parent)
//{

//}

IGraphStatus::~IGraphStatus()
{
  Q_D(IGraphStatus);
  if(d->m_timer->isActive())
  {
    d->m_timer->stop();
    delete d->m_timer;
  }
  delete d->m_alarmInfoItem;
}

void IGraphStatus::visit(IUiWidget *uiWidget)
{
  initPrivateData(uiWidget);
  setUiVersionName();
  setCustomVisitActive(uiWidget);
  setupDataMappings();
  setCommonConnections();
}

void IGraphStatus::setTimerActive(bool active)
{
  Q_D(IGraphStatus);
  if(d->m_timer)
  {
    if(active)
      d->m_timer->start();
    else
      d->m_timer->stop();
  }
}

void IGraphStatus::setCustomVisitActive(IUiWidget *uiWidget)
{
  Q_D(IGraphStatus);

//  Q_UNUSED(uiWidget);
//  QWidget *widget=alarmBackgroundWidget();
//  if(!widget)
//    return;

//  QGridLayout *gridLayout=new QGridLayout(widget);
//  gridLayout->setMargin(35);

//  QString fileName=ALM_DETAIL_FILE_NAME+QString::number(uiWidget->uiIndexs().axisInx%2)+".xml";
//  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(d->m_dev->filePath()+"page/"+fileName);
//  QTreeWidgetItem *alarmItem=tree->topLevelItem(0);

//  int count=alarmItem->childCount();

//  int col=UI_LAYOUT_LED_ALARM_COL;
//  int row=count/col;
//  int remain=count%col;
//  int rsv=0;
//  if(remain>0)
//  {
//    row++;
//    rsv=col-remain;
//  }
//  qDebug()<<tr("col=%1 row=%2 rsv=%3").arg(col).arg(row).arg(rsv);

//  int rowInx=0;
//  int colInx=0;
//  QTreeWidgetItem *item=NULL;
//  QAction *action=NULL;
//  LedAlarm *led=NULL;
//  OptUser *usr=dynamic_cast<OptUser *>(OptContainer::instance()->optItem("optuser"));
//  connect(usr,SIGNAL(usrChange(bool)),this,SLOT(onOptUserChanged(bool)));
//  for(int i=0;i<alarmItem->childCount();i++)
//  {
//    item=alarmItem->child(i);
//    led=new LedAlarm(tr("%1").arg(item->text(GT::COL_PAGE_TREE_INTRODUCT)),this,i);
//    led->setToolTip(tr("Cause:\n%1\nSolution:\n%2").arg(item->text(GT::COL_PAGE_TREE_SCALE+1)).arg(item->text(GT::COL_PAGE_TREE_SCALE+2)));
//    action=new QAction(tr("config mask"),led);
//    led->addMenuAction(action);
//    action=new QAction(tr("save mask"),led);
//    led->addMenuAction(action);
//    action=new QAction(tr("restore"),led);
//    led->addMenuAction(action);
//    led->setMenuActive(usr->isAdmin());
//    d->m_ledAlarmList.append(led);

//    qDebug()<<"addwidget"<<"row"<<rowInx<<"col"<<colInx<<"count"<<i;
//    gridLayout->addWidget(led,rowInx,colInx);
//    rowInx++;
//    if(rowInx>=row)
//    {
//      rowInx=0;
//      colInx++;
//    }
//  }

//  for(int k=0;k<rsv;k++)
//  {
////    led=new LedAlarm(tr("reserve%1").arg(alarmItem->text(GT::COL_PAGE_TREE_ADDR)),this,-1);
//    led=new LedAlarm(tr("reserve"),this,-1);
//    gridLayout->addWidget(led,rowInx,colInx);
//    rowInx++;
//  }
//  widget->setLayout(gridLayout);
//  delete tree;

  addAlarmLedsToWidget(uiWidget);

  addLedErrorTitle();
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QString css=face->css();
  setDeviceStatusIconByCss(css);

  d->m_timer=new QTimer;
  d->m_timer->setInterval(TIMER_INTERVAL);
  connect(d->m_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));

  d->m_sevModeText<<tr("0 IDLE")\
                  <<tr("1 ADC")\
                  <<tr("2 Motor Phase Identify")\
                  <<tr("3 Machine Identify")\
                  <<tr("4 Voltage OMode")\
                  <<tr("5 Current CMode")\
                  <<tr("6 Velocity CMode")\
                  <<tr("7 Position CMode");

  d->m_sevUsrModeText<<tr("0 IDLE")\
                  <<tr("1 ADC")\
                  <<tr("2 Motor Phase Identify")\
                  <<tr("3 Machine Identify")\
                  <<tr("4 Voltage Open")\
                  <<tr("5 Current Close")\
                  <<tr("6 Velocity Close")\
                  <<tr("7 Velocity Profile")\
                  <<tr("8 Sync Velocity")\
                  <<tr("9 Stop")\
                  <<tr("10 Sync Position")\
                  <<tr("11 Plan Stop")\
                  <<tr("12 Sync Current");
  d->m_sevStatusText<<tr("0 OFF")<<tr("1 INIT")<<tr("2 ON");
}

void IGraphStatus::syncTreeDataToUiFace()
{
  Q_D(IGraphStatus);

  LedAlarm *led=NULL;
  quint32 code=alarmCode();
  for(int i=0;i<d->m_ledAlarmList.count();i++)
  {
    quint32 op=0x00000001;
    op<<=i;
    op=op&code;
    led=d->m_ledAlarmList.at(i);
    led->setError((bool)op);
  }

  d->m_ledFlag->setError(hasError());
  updateUiLabelText();

  //读编码器屏蔽寄存器信息
  d->m_dev->readItemFlash(d->m_uiWidget->uiIndexs().axisInx,d->m_alarmInfoItem);
  //将屏蔽寄存器信息更新到第一个led上面
  quint32 maskCode=d->m_alarmInfoItem->text(GT::COL_PAGE_TREE_VALUE).toUInt();
  for(int i=0;i<d->m_ledAlarmList.count();i++)
  {
    quint32 op=0x00000001;
    op<<=i;
    op=op&maskCode;
    led=d->m_ledAlarmList.at(i);
    led->setActionSaveMaskChecked((bool)op);
  }

}

void IGraphStatus::addLedErrorTitle()
{
  Q_D(IGraphStatus);
  d->m_ledFlag=new LedAlarm(tr("CurrentAxis:%1").arg(d->m_uiWidget->uiIndexs().axisInx+1),this,-1,LedAlarm::LED_TEXT_BOTTOM);
  d->m_ledFlag->setActionConfigMaskText(tr("config mask all"));
  d->m_ledFlag->setActionSaveMaskText(tr("save mask all"));
//  d->m_ledFlag->setActionRestoreMaskText(tr("restore mask all"));
  addLedErrorToUi();
}

void IGraphStatus::onFaceCssChanged(const QString &css)
{
  setDeviceStatusIconByCss(css);
}

void IGraphStatus::onTimeOut()
{
  Q_D(IGraphStatus);
  qDebug()<<"Status timeout";
  d->m_uiWidget->readGenPageRAM();
  syncTreeDataToUiFace();
}

void IGraphStatus::onOptUserChanged(bool admin)
{
  Q_D(IGraphStatus);
  foreach (LedAlarm *led, d->m_ledAlarmList) {
    led->setMenuActive(admin);
  }
}

void IGraphStatus::onActnSaveMaskClicked()
{
  Q_D(IGraphStatus);
  LedAlarm *alarm=qobject_cast<LedAlarm *>(sender());
  qDebug()<<"alarm id"<<alarm->id()<<"ischecked"<<alarm->actionSaveMaskIsChecked();

  quint32 maskCode=d->m_alarmInfoItem->text(GT::COL_PAGE_TREE_VALUE).toUInt();
  qDebug()<<"before maskCode"<<QString::number(maskCode,16);

  quint32 op=0x01;
  op<<=alarm->id();
  if(alarm->actionSaveMaskIsChecked())//mask
  {
    maskCode|=op;
  }
  else//unmask
  {
    maskCode&=(~op);
  }
  qDebug()<<"after maskCode"<<QString::number(maskCode,16);
  d->m_alarmInfoItem->setText(GT::COL_PAGE_TREE_VALUE,QString::number(maskCode));
  d->m_dev->writeItemFlash(d->m_uiWidget->uiIndexs().axisInx,d->m_alarmInfoItem);
}

void IGraphStatus::onActnConfigMaskClicked()
{
  LedAlarm *alarm=qobject_cast<LedAlarm *>(sender());
  qDebug()<<"alarm id"<<alarm->id()<<"ischecked"<<alarm->actionConfigMaskIsChecked();
}

void IGraphStatus::onActnRestoreMaskClicked()
{

}

void IGraphStatus::onActnRestoreMaskAllClicked()
{

}

void IGraphStatus::onActnSaveMaskAllClicked()
{

}

void IGraphStatus::addAlarmLedsToWidget(IUiWidget *uiWidget)
{
  Q_D(IGraphStatus);

  Q_UNUSED(uiWidget);
  QWidget *widget=alarmBackgroundWidget();
  if(!widget)
    return;

  QGridLayout *gridLayout=new QGridLayout(widget);
  gridLayout->setMargin(35);

  QString fileName=ALM_DETAIL_FILE_NAME+QString::number(uiWidget->uiIndexs().axisInx%2)+".xml";
  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(d->m_dev->filePath()+"page/"+fileName);
  QTreeWidgetItem *alarmItem=tree->topLevelItem(0);

  d->m_alarmInfoItem=tree->topLevelItem(1)->clone();

  int count=alarmItem->childCount();

  int col=UI_LAYOUT_LED_ALARM_COL;
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
//  QAction *action=NULL;
  LedAlarm *led=NULL;
  OptUser *usr=dynamic_cast<OptUser *>(OptContainer::instance()->optItem("optuser"));
  connect(usr,SIGNAL(usrChange(bool)),this,SLOT(onOptUserChanged(bool)));
  for(int i=0;i<alarmItem->childCount();i++)
  {
    item=alarmItem->child(i);
    led=new LedAlarm(QString("%1").arg(item->text(GT::COL_PAGE_TREE_INTRODUCT)),this,i);
    led->setToolTip(tr("Cause:\n%1\nSolution:\n%2").arg(item->text(GT::COL_PAGE_TREE_SCALE+1)).arg(item->text(GT::COL_PAGE_TREE_SCALE+2)));
    connect(led,SIGNAL(actnConfigMaskTrigger()),this,SLOT(onActnConfigMaskClicked()));
    connect(led,SIGNAL(actnSaveMaskTrigger()),this,SLOT(onActnSaveMaskClicked()));
//    connect(led,SIGNAL(actnRestoreMaskTrigger()),this,SLOT(onActnRestoreMaskClicked()));

//    action=new QAction(tr("config mask"),led);
//    action->setData(QVariant(i));
//    connect(action,SIGNAL(triggered(bool)),this,SLOT(onActnConfigMaskClicked()));
//    action->setCheckable(true);
//    led->addMenuAction(action);

//    action=new QAction(tr("save mask"),led);
//    action->setData(QVariant(i));
//    connect(action,SIGNAL(triggered(bool)),this,SLOT(onActnSaveMaskClicked()));
//    action->setCheckable(true);
//    action->setToolTip(tr("active after reset"));
//    led->addMenuAction(action);

//    action=new QAction(tr("restore"),led);
//    connect(action,SIGNAL(triggered(bool)),this,SLOT(onActnRestoreMaskClicked()));
//    led->addMenuAction(action);

    led->setMenuActive(usr->isAdmin());
    d->m_ledAlarmList.append(led);

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
//    led=new LedAlarm(tr("reserve%1").arg(alarmItem->text(GT::COL_PAGE_TREE_ADDR)),this,-1);
    led=new LedAlarm(tr("reserve"),this,-1);
    gridLayout->addWidget(led,rowInx,colInx);
    rowInx++;
  }
  widget->setLayout(gridLayout);
  delete tree;
}

IGraphStatus::IGraphStatus(IGraphStatusPrivate &dd, QWidget *parent):IGraph(dd,parent)
{

}
