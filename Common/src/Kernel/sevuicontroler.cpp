#include "sevuicontroler.h"
#include "sevdevice.h"
#include "sdtglobaldef.h"
#include "uifactory.h"
#include "iuiwidget.h"
#include "deviceconfig.h"
#include "gtutils.h"

#include "Option"

#include <QDebug>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QTranslator>

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

  setTransLanguage();

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
      index.axisInx=i;
      index.pageInx=j;
      ui->setUiIndexs(index);
      ui->addTreeWidget(m_sev->axisTreeSource(i,j));
//      qDebug()<<"graph name"<<uiGraphName;
      if(uiGraphName!="NULL")
      {
        QWidget *uiGraph=UiFactory::createObject(uiGraphName.toLatin1());
        ui->accept(uiGraph);
      }

      m_uiLists.append(ui);

      sum+=dec;
      emit initProgressInfo((int)sum,tr("build ui %1").arg(className));
    }
  }


  //单个设备中通用模块
  for(int i=0;i<globalItem->childCount();i++)
  {
    className=globalItem->child(i)->text(2);
    ui=dynamic_cast<IUiWidget *> (UiFactory::createObject(className.toLatin1()));
    ui->init(m_sev);
    UiIndexs index;
    index.devInx=m_sev->devId();
    index.axisInx=-1;
    index.pageInx=i;
    ui->setUiIndexs(index);
    ui->addTreeWidget(m_sev->globalTreeSource(i));

    m_uiLists.append(ui);
    sum=100;
    emit initProgressInfo((int)sum,tr("build ui %1").arg(className));
  }
}

SevUiControler::~SevUiControler()
{
  qDebug()<<"SevUiControler-->destruct";
  clearTransLanguage();
  GT::deepClearList(m_uiLists);
}

IUiWidget *SevUiControler::uiWidget(quint32 devInx,qint16 axisInx,const QString &uiName)const
{
  IUiWidget *ui=NULL;
  foreach (IUiWidget *w, m_uiLists)
  {
    UiIndexs indexs=w->uiIndexs();
    if(indexs.devInx==devInx&&indexs.axisInx==axisInx&&w->objectName()==uiName)
    {
      ui=w;
      break;
    }
  }
  return ui;
}

void SevUiControler::setTransLanguage()
{
  QString ver=m_sev->deviceConfig()->m_version;
  OptFace *face=dynamic_cast<OptFace *>(OptContainer::instance()->optItem("optface"));
  QString langPath=GTUtils::languagePath();
  QString lang;
  if(face->language()=="chinese")
    lang=langPath+"ch/";
  else
    lang=langPath+"en/";
  QString path=lang+"page/"+ver+"/";
  qDebug()<<"the language version path="<<path;
  m_transList=GTUtils::setupTranslators(path);
}
void SevUiControler::clearTransLanguage()
{
  foreach (QTranslator *tr, m_transList) {
    qApp->removeTranslator(tr);
  }
  GT::deepClearList(m_transList);
}
