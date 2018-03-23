#include "igraphstatus.h"
#include "igraphstatus_p.h"
#include "ledalarm.h"
#include "qttreemanager.h"
#include "sevdevice.h"
#include "iuiwidget.h"
#include "Option"

#include <QGridLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QLabel>
#include <QAction>
#include <QVBoxLayout>
#include <QTimer>

#define UI_LAYOUT_LED_ALARM_COL 3
#define ALM_DETAIL_FILE_NAME "PrmFuncDeviceStatusAlarmInfo.xml"

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

  Q_UNUSED(uiWidget);
  QWidget *widget=alarmBackgroundWidget();
  if(!widget)
    return;

  QGridLayout *gridLayout=new QGridLayout(widget);
  gridLayout->setMargin(35);

  QTreeWidget *tree=QtTreeManager::createTreeWidgetFromXmlFile(d->m_dev->filePath()+ALM_DETAIL_FILE_NAME);
  QTreeWidgetItem *alarmItem=tree->topLevelItem(0);

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
  QAction *action=NULL;
  LedAlarm *led=NULL;
  OptUser *usr=dynamic_cast<OptUser *>(OptContainer::instance()->optItem("optuser"));
  connect(usr,SIGNAL(usrChange(bool)),this,SLOT(onOptUserChanged(bool)));
  for(int i=0;i<alarmItem->childCount();i++)
  {
    item=alarmItem->child(i);
    led=new LedAlarm(tr("%1").arg(item->text(1)),this,i);
    led->setToolTip(tr("Cause:\n%1\nSolution:\n%2").arg(item->text(2)).arg(item->text(3)));
    action=new QAction(tr("config mask"),led);
    led->addMenuAction(action);
    action=new QAction(tr("save mask"),led);
    led->addMenuAction(action);
    action=new QAction(tr("restore"),led);
    led->addMenuAction(action);
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
    led=new LedAlarm(tr("reserve"),this,-1);

    gridLayout->addWidget(led,rowInx,colInx);
    rowInx++;
  }
  widget->setLayout(gridLayout);
  delete tree;

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
}

void IGraphStatus::addLedErrorTitle()
{
  Q_D(IGraphStatus);
  d->m_ledFlag=new LedAlarm(tr("CurrentAxis:%1").arg(d->m_uiWidget->uiIndexs().axisInx+1),this,-1,LedAlarm::LED_TEXT_BOTTOM);
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
  d->m_uiWidget->readGenRAM();
  syncTreeDataToUiFace();
}

void IGraphStatus::onOptUserChanged(bool admin)
{
  Q_D(IGraphStatus);
  foreach (LedAlarm *led, d->m_ledAlarmList) {
    led->setMenuActive(admin);
  }
}

IGraphStatus::IGraphStatus(IGraphStatusPrivate &dd, QWidget *parent):IGraph(dd,parent)
{

}
