﻿#include "sevuicontroler.h"
#include "sevdevice.h"
#include "sdtglobaldef.h"
#include "UiFactory/uifactory.h"
#include "IUiWidget/iuiwidget.h"

#include <QDebug>
#include <QTreeWidgetItem>

SevUiControler::SevUiControler(SevDevice *sev, GlobalConfig *gconfig, QObject *parent):IUiControler(gconfig,parent),
  m_sev(sev)
{

}
void SevUiControler::createUis()
{
  QTreeWidgetItem *targetTree=m_sev->targetTree();
  Q_ASSERT(targetTree);

  QTreeWidgetItem *axisItem=targetTree->child(0);
  QTreeWidgetItem *globalItem=targetTree->child(1);

  IUiWidget *ui=NULL;
  QString className;
  double sum=65;
  double dec=35.0/(m_sev->axisNum()*axisItem->childCount());
  //与轴相关的模块

  for(int i=0;i<m_sev->axisNum();i++)
  {
    for(int j=0;j<axisItem->childCount();j++)
    {
      className=axisItem->child(j)->text(2);

      ui=dynamic_cast<IUiWidget *> (UiFactory::createObject(className.toLatin1()));
      ui->init(m_sev);
      ui->setUiIndexs(i,j);
      ui->addTreeWidget(m_sev->axisTreeSource(i,j));
      connect(ui,SIGNAL(sglReadPageFlash(int,QTreeWidget*)),m_sev,SLOT(onReadPageFlash(int,QTreeWidget*)));
      connect(ui,SIGNAL(sglWritePageFlash(int,QTreeWidget*)),m_sev,SLOT(onWritePageFlash(int,QTreeWidget*)));

      m_uiLists.append(ui);
//      qDebug()<<"class name "<<ui->objectName();
      sum+=dec;
//      qDebug()<<"sum"<<sum;
      emit initProgressInfo((int)sum,tr("build ui %1").arg(className));
    }
    qDebug()<<"------------------build device ui :"<<i;
  }
  //单个设备中通用模块
  for(int i=0;i<globalItem->childCount();i++)
  {
    className=globalItem->child(i)->text(2);
    ui=dynamic_cast<IUiWidget *> (UiFactory::createObject(className.toLatin1()));
    ui->init(m_sev);
    ui->setUiIndexs(-1,i);
    ui->addTreeWidget(m_sev->globalTreeSource(i));
    connect(ui,SIGNAL(sglReadPageFlash(int,QTreeWidget*)),m_sev,SLOT(onReadPageFlash(int,QTreeWidget*)));

    m_uiLists.append(ui);
//    qDebug()<<"class name "<<ui->objectName();
    sum=100;
//    qDebug()<<"sum"<<sum;
    emit initProgressInfo((int)sum,tr("build ui %1").arg(className));
  }
}

SevUiControler::~SevUiControler()
{
  qDebug()<<"SevUiControler-->destruct";
  GT::deepClearList(m_uiLists);
}
