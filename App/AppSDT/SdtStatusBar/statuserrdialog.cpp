#include "statuserrdialog.h"
#include "ui_statuserrdialog.h"

#include <QDebug>

#include "sdtglobaldef.h"
#define STATUS_CLASSNAME "UiStatus"
using namespace GT;

StatusErrDialog::StatusErrDialog(QTreeWidget *navTree, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StatusErrDialog)
{
  ui->setupUi(this);
  connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onTreeWidgetItemClicked(QTreeWidgetItem*,int)));
  updateDevice(navTree);
}

StatusErrDialog::~StatusErrDialog()
{
  delete ui;
  qDebug()<<"StatusErrDialog destruct-->";
}
void StatusErrDialog::updateDevice(QTreeWidget *navTree)
{
  ui->treeWidget->clear();
  QTreeWidgetItem *itemDev,*itemDevSrc;
  QTreeWidgetItem *itemAxisSrc;
  QTreeWidgetItem *itemStatus,*itemStatusSrc;

  for(int i=0;i<navTree->topLevelItemCount();i++)
  {
    int axisNum;
    itemDevSrc=navTree->topLevelItem(i);
    if(itemDevSrc->text(COL_TARGET_CONFIG_PRM)!="-1")//-1代表不是设备，是全局结点
    {
      itemDev=new QTreeWidgetItem(ui->treeWidget);
      itemDev->setText(0,itemDevSrc->text(COL_TARGET_CONFIG_NAME));
      axisNum=itemDevSrc->text(COL_TARGET_CONFIG_PRM).toInt();
      for(int j=0;j<axisNum;j++)
      {
        itemStatus=new QTreeWidgetItem(itemDev);
        itemAxisSrc=itemDevSrc->child(j);
        itemStatus->setText(0,itemAxisSrc->text(COL_TARGET_CONFIG_NAME));
//        qDebug()<<"itemAxisSrc->text(COL_TARGET_CONFIG_NAME)"<<itemAxisSrc->text(COL_TARGET_CONFIG_NAME);
        setItemStatus(itemStatus,true);
        itemStatusSrc=findStatusItem(itemAxisSrc);
        if(itemStatusSrc!=NULL)
          itemStatus->setText(2,itemStatusSrc->text(COL_TARGET_CONFIG_INDEX));
        else
          itemStatus->setText(2,"-1");
      }
    }
  }
  ui->treeWidget->expandAll();
}

void StatusErrDialog::setStatusError(quint32 devInx, qint16 axis, bool hasErr)
{
  QTreeWidgetItem *item=ui->treeWidget->topLevelItem(devInx);
  if(item!=NULL)
  {
    QTreeWidgetItem *itemChild=item->child(axis);
    setItemStatus(itemChild,!hasErr);
  }
}

void StatusErrDialog::onTreeWidgetItemClicked(QTreeWidgetItem *item, int column)
{
  Q_UNUSED(column);
  if(item->childCount()==0)
  {
    int pageIndex=item->text(2).toInt();
    emit statusPageChanged(pageIndex);
    qDebug()<<"emit statusPageChanged"<<pageIndex;
  }
}

void StatusErrDialog::setItemStatus(QTreeWidgetItem *item,bool status)
{
  if(status)
  {
    item->setText(1,"OK");
  }
  else
    item->setText(1,"Error");
}
QTreeWidgetItem *StatusErrDialog::findStatusItem(QTreeWidgetItem *axisItem) const
{
  QTreeWidgetItem *item=NULL;
  for(int i=0;i<axisItem->childCount();i++)
  {
    if(axisItem->child(i)->text(COL_TARGET_CONFIG_CLASS)==STATUS_CLASSNAME)
    {
      item=axisItem->child(i);
//      qDebug()<<"find item"<<item->text(0);
      break;
    }
  }
  return item;
}
