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

#define UI_LAYOUT_LED_ALARM_COL 4
#define ALM_DETAIL_FILE_NAME "PrmFuncDeviceStatusAlarmInfo.xml"
#define ALM_CODE_ALL_INX 3


IGraphStatusPrivate::IGraphStatusPrivate():
  m_ledFlag(NULL)
{

}

IGraphStatusPrivate::~IGraphStatusPrivate()
{

}

//IGraphStatus::IGraphStatus(QWidget *parent) : IGraph(*(new IGraphStatusPrivate),parent)
//{

//}

IGraphStatus::~IGraphStatus()
{

}

void IGraphStatus::visit(IUiWidget *uiWidget)
{
  initPrivateData(uiWidget);
  setUiVersionName();
  setCustomVisitActive(uiWidget);
  setupDataMappings();
  setCommonConnections();
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
  LedAlarm *led=NULL;
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
    led=new LedAlarm(tr("hello %1").arg(rowInx),this,-1);

    gridLayout->addWidget(led,rowInx,colInx);
    rowInx++;
  }
  widget->setLayout(gridLayout);
  delete tree;

  addLedErrorTitle();
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QString css=face->css();
  setDeviceStatusIconByCss(css);

}

void IGraphStatus::addLedErrorTitle()
{
  Q_D(IGraphStatus);
  d->m_ledFlag=new LedAlarm(tr("CurrentAxis:%1").arg(d->m_uiWidget->uiIndexs().axisInx),this,-1,LedAlarm::LED_TEXT_BOTTOM);
  addLedErrorToUi();
}

void IGraphStatus::onFaceCssChanged(const QString &css)
{
  setDeviceStatusIconByCss(css);
}

IGraphStatus::IGraphStatus(IGraphStatusPrivate &dd, QWidget *parent):IGraph(dd,parent)
{

}
