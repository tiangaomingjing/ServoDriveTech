#include "generalcmd.h"
#include "icom.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>

GeneralCmd* GeneralCmd::m_instance=NULL;

class GeneralCmd::GeneralCmdPrivateData
{
public:
  GeneralCmdPrivateData(){}
  ~GeneralCmdPrivateData(){}

  typedef struct{
    QString type;
    QString unit;
    int cmd;
    int length;
    int setIndex;
    int getIndex;
    double kgain;
    int id;
  }CmdTreeData;

  QMap<QString ,CmdTreeData>m_cmdMaps;
};


GeneralCmd *GeneralCmd::instance(QObject *parent)
{
  static QMutex mutex;
  if(!m_instance)
  {
    QMutexLocker locker(&mutex);
    if(!m_instance)
      m_instance=new GeneralCmd(parent);
  }
  return m_instance;
}
GeneralCmd::GeneralCmd(QObject *parent):QObject(parent),m_dataPtr(new GeneralCmdPrivateData)
{
}
bool GeneralCmd::fillCmdMaps(QTreeWidget *cmdTree)
{
  m_dataPtr->m_cmdMaps.clear();
  QTreeWidgetItem *topItem;
  for(int i=0;i<cmdTree->topLevelItemCount();i++)
  {
    topItem=cmdTree->topLevelItem(i);
    fillItemMaps(topItem);
  }
#if 1
  QMapIterator<QString,GeneralCmdPrivateData::CmdTreeData>i(m_dataPtr->m_cmdMaps);
  const GeneralCmdPrivateData::CmdTreeData *data;
  while(i.hasNext()){
    i.next();
    data=&(i.value());
    qDebug()<<"cmd map:"<<i.key()<<" "<<data->type<<data->unit<<data->cmd<<data->length<<data->setIndex<<data->getIndex<<data->kgain<<data->id;
  }
#endif
  return true;
}

double GeneralCmd::read(const QString &cmdReadName,qint16 axisIndex,bool &isOk,ComDriver::ICom *icom)
{
  double ret=-1;
  int getIndex=0;
  double kgain;
  int id;
  ushort cmd;
  ushort length;
  QString dataType;
  ComDriver::GeneralPDU funcRead;

  isOk=true;
  //获取cmd相关信息
  const GeneralCmdPrivateData::CmdTreeData *data;
  if(!m_dataPtr->m_cmdMaps.contains(cmdReadName))//如果cmdtree中没有这个名字，则返回 0
    return 0;
  data=&(m_dataPtr->m_cmdMaps.value(cmdReadName));
  id=data->id;
  getIndex=data->getIndex;
  kgain=data->kgain;
  cmd=data->cmd;
  length=data->length;
  dataType=data->type;

  funcRead.mode=1;//1:为读    0：写
  funcRead.cmd=cmd;
  funcRead.subId=id;
  funcRead.length=length;

  if(0!=GTSD_CMD_ProcessorGeneralFunc(axisIndex,&funcRead,m_comType,m_comRnStation))
  {
    if(0!=GTSD_CMD_ProcessorGeneralFunc(axisIndex,&funcRead,m_comType,m_comRnStation))
      return -1;
  }

  if(dataType.contains("32"))//32位
  {
    if(dataType.contains("U"))
    {
      Uint32 value;
      Uint32 temp;
      temp=funcRead.data[getIndex+1];//低位在前
      temp=temp&0x0000ffff;
      temp=(temp<<16)&0xffff0000;
      value=temp+(funcRead.data[getIndex]&0x0000ffff);
      ret=value+0.0;
    }
    else
    {
      int32 value;
      int32 temp;
      temp=funcRead.data[getIndex+1];
      temp=temp&0x0000ffff;
      temp=(temp<<16)&0xffff0000;
      value=temp+(funcRead.data[getIndex]&0x0000ffff);
      ret=value+0.0;
    }
  }
  else//16位
  {
    if(dataType.contains("U"))
    {
      Uint16 value;
      value=funcRead.data[getIndex];
      ret=value+0.0;
    }
    else
    {
      int16 value;
      value=funcRead.data[getIndex];
      ret=value+0.0;
    }
  }
  ret=ret/kgain;
  delete []funcRead.data;
  return ret;
  return 0;
}

double GeneralCmd::write(const QString &cmdWriteName,double value,qint16 axisIndex,bool &isOk,ComDriver::ICom *icom)
{
  return 0;
}

void GeneralCmd::fillItemMaps(QTreeWidgetItem *item)
{
  QTreeWidgetItem *childItem;
  for(int i=0;i<item->childCount();i++)
  {
    childItem=item->child(i);
    if(childItem->childCount()>0)
    {
      fillItemMaps(childItem);
    }
    else
    {
      QString name=childItem->text(COL_CMD_FUNC_NAME);
      QString type=childItem->text(COL_CMD_FUNC_TYPE);
      QString unit=childItem->text(COL_CMD_FUNC_UNIT);
      int cmd=childItem->text(COL_CMD_FUNC_CMD).toInt();
      int length=childItem->text(COL_CMD_FUNC_LENGTH).toInt();
      int setIndex=childItem->text(COL_CMD_FUNC_SETINDEX).toInt();
      int getIndex=childItem->text(COL_CMD_FUNC_GETINDEX).toInt();
      double kgain=childItem->text(COL_CMD_FUNC_KGAIN).toDouble();
      int id=childItem->text(COL_CMD_FUNC_ID).toInt();
      GeneralCmdPrivateData::CmdTreeData treeData;
      treeData.type=type;
      treeData.unit=unit;
      treeData.cmd=cmd;
      treeData.length=length;
      treeData.setIndex=setIndex;
      treeData.getIndex=getIndex;
      treeData.kgain=kgain;
      treeData.id=id;
      m_dataPtr->m_cmdMaps.insert(name,treeData);
    }
  }
}
