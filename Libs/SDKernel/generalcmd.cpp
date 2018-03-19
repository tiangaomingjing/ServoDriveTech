#include "generalcmd.h"
#include "icom.h"

#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>

#define TEST_OUT 1

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
  ComDriver::ICom *m_icom;
  ComDriver::errcode_t m_errorCode;
};


GeneralCmd::GeneralCmd(ComDriver::ICom *icom, QObject *parent):QObject(parent),m_dataPtr(new GeneralCmdPrivateData)
{
  m_dataPtr->m_icom=icom;
}
GeneralCmd::~GeneralCmd()
{
  delete m_dataPtr;
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

//!
//! \brief read
//! \param cmdReadName
//! \param axisIndex
//! \param isOk 通信是否正确返回
//! \return 回来的是原始的数值，增益转化在界面的树结构中
//!
quint64 GeneralCmd::read(const QString &cmdReadName, qint16 axisIndex, bool &isOk)
{
  quint64 ret=0;
  int getIndex=0;
  double kgain;
  int id;
  ushort cmd;
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
  dataType=data->type;

  funcRead.mode=ComDriver::GENERAL_PDU_READ;//1:为读    0：写
  funcRead.cmd=cmd;
  funcRead.subId=id;

  if(dataType.contains("16"))
    funcRead.length=1;
  else if(dataType.contains("32"))
    funcRead.length=2;
  else if(dataType.contains("64"))
    funcRead.length=4;
  else
    funcRead.length=1;


  ComDriver::errcode_t err=m_dataPtr->m_icom->sendGeneralCmd(axisIndex,funcRead);
  if(err!=0)
    err=m_dataPtr->m_icom->sendGeneralCmd(axisIndex,funcRead);
  if(err!=0)
  {
    isOk=false;
    qDebug()<<"GeneralCmd read error:icom->sendGeneralCmd(axisIndex,funcRead)";
  }

  if(isOk)
  {
    for(int i=0;i<funcRead.length;i++)
      ret+=funcRead.data[i]<<(16*i);
#if TEST_OUT
    for(int i=0;i<funcRead.length;i++)
    {
      qDebug()<<"read raw data["<<i<<"]="<<funcRead.data[i];
    }
#endif
  }

  m_dataPtr->m_errorCode=err;
  return ret;
}

qint16 GeneralCmd::readErrorCode()
{
  return m_dataPtr->m_errorCode;
}

//!
//! \brief GeneralCmd::write
//! \param cmdWriteName
//! \param value  写的是最终的数据，value=GraphUI上的数据先*tree的增益
//! \param axisIndex
//! \return
//!
bool GeneralCmd::write(const QString &cmdWriteName, quint64 value, qint16 axisIndex)
{
  int getIndex=0;
  double kgain;
  int id;
  ushort cmd;
  QString dataType;
  ComDriver::GeneralPDU funcWrite;

  //获取cmd相关信息
  const GeneralCmdPrivateData::CmdTreeData *data;
  if(!m_dataPtr->m_cmdMaps.contains(cmdWriteName))//如果cmdtree中没有这个名字，则返回 0
    return true;
  data=&(m_dataPtr->m_cmdMaps.value(cmdWriteName));
  id=data->id;
  getIndex=data->getIndex;
  kgain=data->kgain;
  cmd=data->cmd;
  dataType=data->type;

  funcWrite.mode=ComDriver::GENERAL_PDU_WRITE;//1:为读    0：写
  funcWrite.cmd=cmd;
  funcWrite.subId=id;


  if(dataType.contains("16"))
    funcWrite.length=1;
  else if(dataType.contains("32"))
    funcWrite.length=2;
  else if(dataType.contains("64"))
    funcWrite.length=4;
  else
    funcWrite.length=1;

  qDebug()<<"funcWrite.mode"<<funcWrite.mode<<"funcWrite.cmd"<<funcWrite.cmd<<"funcWrite.subId"<<funcWrite.subId<<"funcWrite.length"<<funcWrite.length;

  for(int i=0;i<funcWrite.length;i++)
  {
    funcWrite.data[i]=value>>16*i;
#if TEST_OUT
    qDebug()<<"write data["<<i<<"]="<<funcWrite.data[i];
#endif
  }

  ComDriver::errcode_t err=m_dataPtr->m_icom->sendGeneralCmd(axisIndex,funcWrite);
  if(err!=0)
    err=m_dataPtr->m_icom->sendGeneralCmd(axisIndex,funcWrite);
  if(err!=0)
  {
    qDebug()<<"GeneralCmd write error:icom->sendGeneralCmd(axisIndex,funcRead)";
    return false;
  }
  return true;

//  quint64 ret=0;
//  bool isOk=true;
//  ret=read(cmdWriteName,axisIndex,isOk);
//  if(isOk)
//  {
//    if(ret==value)
//      isOk=true;
//    else
//    {
//      isOk=false;
//      qDebug()<<"GeneralCmd write error:write value!=read value";
//    }
//  }
  //  return isOk;
}

bool GeneralCmd::containsCmd(const QString &cmdName)
{
  return m_dataPtr->m_cmdMaps.contains(cmdName);
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
