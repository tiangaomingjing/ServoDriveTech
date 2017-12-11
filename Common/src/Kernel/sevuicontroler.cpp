#include "sevuicontroler.h"
#include "sevdevice.h"
#include "sdtglobaldef.h"
#include "UiFactory/uifactory.h"
#include "IUiWidget/iuiwidget.h"
#include "UiMotor/uimotor.h"

#include <QDebug>
#include <QTreeWidgetItem>

SevUiControler::SevUiControler(SevDevice *sev, GlobalConfig *gconfig, QObject *parent):IUiControler(sev,gconfig,parent)
{

}
void SevUiControler::createUis()
{
  QTreeWidgetItem *targetTree=m_sev->targetTree();
  QTreeWidgetItem *axisItem=targetTree->child(0);
  QTreeWidgetItem *globalItem=targetTree->child(1);
  QTreeWidgetItem *plotItem=targetTree->child(2);

  IUiWidget *ui=NULL;
  QString className;
  double sum=65;
  double dec=35.0/(m_sev->axisNum()*axisItem->childCount());
  for(int i=0;i<m_sev->axisNum();i++)
  {
    for(int j=0;j<axisItem->childCount();j++)
    {
      className=axisItem->child(j)->text(2);
      ui=dynamic_cast<IUiWidget *> (UiFactory::createObject(className.toLatin1()));
      ui->init();
      m_uiLists.append(ui);
      qDebug()<<"class name "<<ui->objectName();
      sum+=dec;
//      qDebug()<<"sum"<<sum;
      emit initProgressInfo((int)sum,tr("build ui %1").arg(className));
    }
    qDebug()<<"------------------build device ui :"<<i;

  }
  for(int i=0;i<globalItem->childCount();i++)
  {
    className=globalItem->child(i)->text(2);
    ui=dynamic_cast<IUiWidget *> (UiFactory::createObject(className.toLatin1()));
    ui->init();
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
