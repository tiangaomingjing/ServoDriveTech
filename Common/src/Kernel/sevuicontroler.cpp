#include "sevuicontroler.h"
#include "sevdevice.h"
#include "sdtglobaldef.h"
#include "uifactory.h"
#include "iuiwidget.h"

#include <QDebug>
#include <QTreeWidgetItem>

SevUiControler::SevUiControler(SevDevice *sev, QObject *parent):IUiControler(parent),
  m_sev(sev)
{

}
void SevUiControler::createUis()
{
  QTreeWidgetItem *targetTree=m_sev->targetTree();
//  QTreeWidget *t=new QTreeWidget;
//  t->addTopLevelItem(targetTree);
//  t->setColumnCount(7);
//  t->show();

  Q_ASSERT(targetTree);

  QTreeWidgetItem *axisItem=targetTree->child(0);
  QTreeWidgetItem *globalItem=targetTree->child(1);

  IUiWidget *ui=NULL;
  QString className;
  QString uiGraphName;
  double sum=65;
  double dec=35.0/(m_sev->axisNum()*axisItem->childCount());
  //与轴相关的模块

  for(int i=0;i<m_sev->axisNum();i++)//哪一个轴
  {
    for(int j=0;j<axisItem->childCount();j++)//哪一页
    {
      className=axisItem->child(j)->text(2);
      uiGraphName=axisItem->child(j)->text(6);

      ui=dynamic_cast<IUiWidget *> (UiFactory::createObject(className.toLatin1()));
      ui->init(m_sev);
      UiIndexs index;
      index.devInx=m_sev->devId();
      index.aixsInx=i;
      index.pageInx=j;
      ui->setUiIndexs(index);
      ui->addTreeWidget(m_sev->axisTreeSource(i,j));
//      qDebug()<<"graph name"<<uiGraphName;
      if(uiGraphName!="NULL")
      {
        QWidget *uiGraph=UiFactory::createObject(uiGraphName.toLatin1());
        ui->addGraphWidget(uiGraph);
      }
//      ui->createQmlWidget();


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
    UiIndexs index;
    index.devInx=m_sev->devId();
    index.aixsInx=-1;
    index.pageInx=i;
    ui->setUiIndexs(index);
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

IUiWidget *SevUiControler::uiWidget(quint32 devInx,qint16 axisInx,const QString &uiName)const
{
  IUiWidget *ui=NULL;
  foreach (IUiWidget *w, m_uiLists)
  {
    UiIndexs indexs=w->uiIndexs();
    if(indexs.devInx==devInx&&indexs.aixsInx==axisInx&&w->objectName()==uiName)
    {
      ui=w;
      break;
    }
  }
  return ui;
}
