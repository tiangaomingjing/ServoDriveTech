#include "controlservo.h"
#include "globaldefine.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QString>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>
#define TEST_DEBUG 0



ControlServo::ControlServo(QObject *parent) : QObject(parent)
{

}

ControlServo::~ControlServo()
{

}

//写单个树结点
void ControlServo::writeServoFlash(QTreeWidgetItem *item, int axisIndex, COM_TYPE comtype,short comStation)
{
  int16 value16 = 0;
  int32 value32 = 0;
  int64 value64 = 0;
  int64 value = 0;
  int16 offsetValue = 0;
  QString itemType;
  int16 result=0;//0代表成功返回

  offsetValue = item->text(COL_ADDRESS).toInt();
  if (offsetValue != -1)
  {
    value=item->text(COL_VALUE).toLongLong();
    itemType = item->text(COL_TYPE);
    if (itemType.contains("64"))
    {
      result=GTSD_CMD_Fram_Write64BitByAdr(axisIndex,(int16)offsetValue,(int64)value,(int16)comtype,comStation);
      if(result!=0)
        result=GTSD_CMD_Fram_Write64BitByAdr(axisIndex,(int16)offsetValue,(int64)value,(int16)comtype,comStation);

      if(result==0)
      {
//        qDebug()<<"write value to servo flash";
        result=GTSD_CMD_Fram_Read64BitByAdr(axisIndex, (int16)offsetValue, &value64, (int16)comtype,comStation);
        if(result==0)
        {
          if(itemType.contains("U"))
            item->setText(COL_VALUE, QString::number((Uint64)value64));
          else
            item->setText(COL_VALUE, QString::number(value64));
        }
      }
    }
    else if (itemType.contains("32"))
    {
      result=GTSD_CMD_Fram_Write32BitByAdr(axisIndex,(int16)offsetValue,(int32)value,(int16)comtype,comStation);
      if(result!=0)
        result=GTSD_CMD_Fram_Write32BitByAdr(axisIndex,(int16)offsetValue,(int32)value,(int16)comtype,comStation);

      if(result==0)
      {
//        qDebug()<<"write value to servo flash";
        result=GTSD_CMD_Fram_Read32BitByAdr(axisIndex, (int16)offsetValue, &value32, (int16)comtype,comStation);
        if(result==0)
        {
          if(itemType.contains("U"))
            item->setText(COL_VALUE, QString::number((Uint32)value32));
          else
            item->setText(COL_VALUE, QString::number(value32));
        }
      }
    }
    else
    {
      result=GTSD_CMD_Fram_Write16BitByAdr(axisIndex,(int16)offsetValue,(int16)value,(int16)comtype,comStation);
      if(result!=0)
        result=GTSD_CMD_Fram_Write16BitByAdr(axisIndex,(int16)offsetValue,(int16)value,(int16)comtype,comStation);

      if(result==0)
      {
//        qDebug()<<"write value to servo flash";
        result=GTSD_CMD_Fram_Read16BitByAdr(axisIndex, (int16)offsetValue, &value16, (int16)comtype,comStation);
        if(result==0)
        {
          if(itemType.contains("U"))
            item->setText(COL_VALUE, QString::number((Uint16)value16));
          else
            item->setText(COL_VALUE, QString::number(value16));
        }
      }
    }
  }
}

void ControlServo::writeServoFlashByAxisTree(QTreeWidget *tree, int axisIndex, COM_TYPE comtype,short comStation)
{
  QTreeWidgetItemIterator it(tree);
  QTreeWidgetItem *item;
  quint32 count=totalItemCount(tree);
  quint32 index=0;
  qDebug()<<"totalcount="<<count;
  double value;
  while (*it)
  {
    item=(*it);
    index++;
    writeServoFlash(item, axisIndex, comtype,comStation);
    it++;
    value=((index+0.0)/(count+0.0))*100;
//    qDebug()<<"index="<<index<<"value="<<value;
    emit progressValue((int)value);
  }
}

void ControlServo::writeServoFlashByAllAxisTree(QTreeWidget *alltree, COM_TYPE comtype,short comStation)
{
  QTreeWidget *tree;
  QTreeWidgetItem *treeItem;
  for(int i=0;i<alltree->topLevelItemCount();i++)
  {
    tree=new QTreeWidget();
    treeItem=alltree->topLevelItem(i)->clone();
    tree->addTopLevelItem(treeItem);
    writeServoFlashByAxisTree(tree,i,comtype,comStation);
    tree->clear();
    delete tree;
    tree=NULL;
  }
}

quint32 ControlServo::totalItemCount(QTreeWidget*tree)
{
  QTreeWidgetItemIterator it(tree);
  quint32 count=0;
  while (*it)
  {
    count++;
    it++;
  }
  return count;
}
