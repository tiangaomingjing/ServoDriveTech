#include "powertreemanage.h"
#include "sdkernel_global.h"
#include "qttreemanager.h"
#include "gtutils.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QMessageBox>
#define INX_CURRENT_SAMPLING_TYPE_NAME  "axis.cur.sampling"
#define INX_CURRENT_SAMPLING_RES_VALUE  "axis.cur.sampling.shunt.res.value"
typedef enum{
  PWR_ROW_INX_XML,
  PWR_ROW_INX_BASIC
}PowerTreeRowIndex;
typedef enum{
  DEV_ROW_INX_BASICINFO,
  DEV_ROW_INX_DETAILINFO
}DeviceRowIndex;
typedef enum{
  DETINFO_ROW_INX_AXISNUM
}DetailInfoRowInx;

enum PwrColumnInx{
  PWR_COL_INX_NAME,
  PWR_COL_INX_VALUE,
  PWR_COL_INX_UNIT,
  PWR_COL_INX_SCALE,
  PWR_COL_INX_DESCRIPTION,
  PWR_COL_INX_TYPE,
  PWR_COL_INX_ADDR,
  PWR_COL_INX_CTLNAME,
  PWR_COL_INX_CTLMAX,
  PWR_COL_INX_CTLMIN,
  PWR_COL_INX_UNIQUENAME
};

SamplingDataInfo::SamplingDataInfo()
{

}
SamplingDataInfo::~SamplingDataInfo()
{

}


QVector<double> SamplingDataInfo::values() const
{
  return m_values;
}

void SamplingDataInfo::setValues(const QVector<double> &values)
{
  m_values = values;
}

QVector<quint8> SamplingDataInfo::types() const
{
  return m_types;
}

void SamplingDataInfo::setTypes(const QVector<quint8> &types)
{
  m_types = types;
}

QStringList SamplingDataInfo::mathExp() const
{
  return m_mathExp;
}

void SamplingDataInfo::setMathExp(const QStringList &mathExp)
{
  m_mathExp = mathExp;
}


PowerTreeManage::PowerTreeManage(DeviceConfig *sev, QObject *parent) : QObject(parent)
//  m_powerTree(powerTree),
//  mp_pwrTarget(NULL)
{
    m_powerTree = NULL;
    mp_pwrTarget = NULL;
    m_sev = sev;
    QString idStr = QString::number(m_sev->m_pwrId, 10);
    qDebug()<<idStr;
    QString path = GTUtils::databasePath() + "Board/PB/";
    QString filePath = path + "pbindex.ui";
    qDebug()<<filePath;
    QTreeWidget *indexTree = QtTreeManager::createTreeWidgetFromXmlFile(filePath);
    QTreeWidgetItem* targetItem = GTUtils::findItem(idStr, indexTree, PWR_COL_INX_VALUE);
    if (targetItem == NULL) {
        qDebug()<<"null";
        return;
    }
    QString itemPath = path + getPath(targetItem);
    qDebug()<<"itemPath "<<itemPath;
    m_filterPath = path + getFilterPath(targetItem);
    qDebug()<<"filterPath"<<m_filterPath;
    m_powerTree = QtTreeManager::createTreeWidgetFromXmlFile(itemPath);
    mp_pwrTarget = GTUtils::findItem(idStr, m_powerTree, PWR_COL_INX_VALUE);
    delete indexTree;
}

PowerTreeManage::~PowerTreeManage() {
    delete m_powerTree;
}

/**
 * @brief PowerTreeManage::findTargetBoard
 * @param id
 * @return NULL :没有找到
 */
//QTreeWidgetItem *PowerTreeManage::findTargetBoard(const quint32 id)
//{
//  QTreeWidgetItem *itemLevel_1;
//  QTreeWidgetItem *itemLevel_2;
//  QTreeWidgetItem *itemLevel_3;
//  QTreeWidgetItem *itemLevel_4;
//  QTreeWidgetItem *retItem=NULL;
//  for(int i=0;i<m_powerTree->topLevelItem(PWR_ROW_INX_BASIC)->childCount();i++)
//  {
//    itemLevel_1=m_powerTree->topLevelItem(PWR_ROW_INX_BASIC)->child(i);
//    qDebug()<<"level 1 "<<itemLevel_1->text(0);
//    for(int j=0;j<itemLevel_1->childCount();j++)
//    {
//      itemLevel_2=itemLevel_1->child(j);
//      qDebug()<<"level 2 "<<itemLevel_2->text(0);
//      for(int k=0;k<itemLevel_2->childCount();k++)
//      {
//        itemLevel_3=itemLevel_2->child(k);
//        qDebug()<<"level 3 "<<itemLevel_3->text(0);
//        for(int n=0;n<itemLevel_3->childCount();n++)
//        {
//          itemLevel_4=itemLevel_3->child(n);
//          qDebug()<<"level 4 "<<itemLevel_4->text(0);
//          if(itemLevel_4->text(PWR_COL_INX_VALUE).toUInt()==id)
//          {
//            retItem=itemLevel_4;
//            qDebug()<<"find id item:"<<retItem->text(0)<<"="<<retItem->text(1);
//            return retItem;
//          }
//        }
//      }
//    }
//  }
//  return NULL;
//}
/**
 * @brief PowerTreeManage::powerLimitMapList
 * @param id 设备EPROM ID
 * @return
 */
QTreeWidgetItem* PowerTreeManage::basicInfoTreeItem(QTreeWidgetItem*target)
{
  QTreeWidgetItem *basicItem;
  basicItem=target->child(DEV_ROW_INX_BASICINFO);

  return basicItem;
}
QTreeWidgetItem * PowerTreeManage::detailInfoTreeItem(QTreeWidgetItem *target)
{
  QTreeWidgetItem *detailItem;
  //detailed information
  detailItem=target->child(DEV_ROW_INX_DETAILINFO);

  return detailItem;
}

bool PowerTreeManage::updatePowerLimitMapList(QList<QMap<QString, PowerBoardLimit> > &powerLimitMapList)
{
  if(mp_pwrTarget==NULL)
    return false;

  int axisNum;
//  QTreeWidgetItem *item;
  powerLimitMapList.clear();
  m_filterPath = m_filterPath + m_sev->m_version + "/" + m_sev->m_version + ".ui";
  qDebug()<<"filterpath "<<m_filterPath;
  QTreeWidget* filterTree = QtTreeManager::createTreeWidgetFromXmlFile(m_filterPath);

  for (int i = 0; i < filterTree->topLevelItemCount(); i++) {
      m_filterList.append(filterTree->topLevelItem(i)->text(0));
  }
  //basic information
  QTreeWidgetItem *basicItem = basicInfoTreeItem(mp_pwrTarget);
  //detailed information
  QTreeWidgetItem *detailItem = detailInfoTreeItem(mp_pwrTarget);
  axisNum=detailItem->child(DETINFO_ROW_INX_AXISNUM)->childCount();

  for(int i=0;i < axisNum; i++)
  {
    QMap<QString ,PowerBoardLimit> plimitMap;
    //basic
    insertLimit(basicItem,plimitMap);
    //detail
    insertLimit(detailItem->child(DETINFO_ROW_INX_AXISNUM)->child(i),plimitMap);
    powerLimitMapList.append(plimitMap);
  }
//  for(int i=0;i<powerLimitMapList.count();i++)
//  {
//    qDebug()<<"axis="<<i;
//    QMapIterator<QString ,PowerBoardLimit> mapIt(powerLimitMapList.at(i));
//    while (mapIt.hasNext()) {
//      mapIt.next();
//      qDebug()<<mapIt.key()<<" max="<<mapIt.value().max<<" min="<<mapIt.value().min;
//    }
//  }
  delete filterTree;
  return true;
}

SamplingDataInfo PowerTreeManage::samplingDataInfo(bool *isOK)
{
  SamplingDataInfo samplingInfo;
  *isOK=true;
  if(mp_pwrTarget==NULL)
  {
      *isOK=false;
      return samplingInfo;
  }
qDebug()<<*isOK;
  QTreeWidgetItem *detailItem = detailInfoTreeItem(mp_pwrTarget);
  int axisNum;
  axisNum=detailItem->child(DETINFO_ROW_INX_AXISNUM)->childCount();
  QVector<quint8> types;
  QVector<double> values;
  for(int i=0;i<axisNum;i++)
  {
    QTreeWidgetItem *axisItem=detailItem->child(DETINFO_ROW_INX_AXISNUM)->child(i);
    QTreeWidgetItem *typeItem=NULL;
    typeItem=findItemByName(axisItem,QString(INX_CURRENT_SAMPLING_TYPE_NAME));
    quint8 type=0;
    double value=0;
    if(typeItem!=NULL)
    {
//      qDebug()<<typeItem->text(0);
      type=typeItem->text(PWR_COL_INX_VALUE).toUInt();
      if(type==1)//电阻采样
      {
        QTreeWidgetItem *dataItem=findItemByName(typeItem,QString(INX_CURRENT_SAMPLING_RES_VALUE));
        if(dataItem!=NULL)
        {
          value=dataItem->text(PWR_COL_INX_VALUE).toDouble();
//          qDebug()<<"type="<<type<<" value="<<value<<" "<<dataItem->text(PWR_COL_INX_UNIQUENAME);
        }
        else
        {
          QMessageBox::information(0,tr("error"),tr("cannot find Sampling type item"));
        }
      }
      else if(type==0)//霍尔采样
      {
        QMessageBox::information(0,tr("warnning"),tr("hall sampling"));
      }
    }
    else
    {
      QMessageBox::information(0,tr("error"),tr("cannot find Sampling type item"));
      *isOK=false;
    }
    types.append(type);
    values.append(value);
  }
  samplingInfo.setTypes(types);
  samplingInfo.setValues(values);
  return samplingInfo;
}

void PowerTreeManage::insertLimit(QTreeWidgetItem *item, QMap<QString ,PowerBoardLimit> &limitMap)
{
  if((item->text(PWR_COL_INX_CTLNAME)!="null")&&(item->text(PWR_COL_INX_CTLNAME)!="") && m_filterList.contains(item->text(PWR_COL_INX_CTLNAME), Qt::CaseSensitive))
  {
    QString name=item->text(PWR_COL_INX_CTLNAME);
    PowerBoardLimit limit;
    limit.max=item->text(PWR_COL_INX_CTLMAX).toDouble();
    limit.min=item->text(PWR_COL_INX_CTLMIN).toDouble();
    limitMap.insert(name,limit);
  }
  insertLimitRecursion(item, limitMap);
}

void PowerTreeManage::insertLimitRecursion(QTreeWidgetItem *item, QMap<QString, PowerBoardLimit> &limitMap)
{
  QTreeWidgetItem *itemChild;
  for(int i=0;i<item->childCount();i++)
  {
    itemChild=item->child(i);
    if((itemChild->text(PWR_COL_INX_CTLNAME)!="null")&&(itemChild->text(PWR_COL_INX_CTLNAME)!="") && m_filterList.contains(item->text(PWR_COL_INX_CTLNAME), Qt::CaseSensitive))
    {
      QString name=itemChild->text(PWR_COL_INX_CTLNAME);
      PowerBoardLimit limit;
      limit.max=itemChild->text(PWR_COL_INX_CTLMAX).toDouble();
      limit.min=itemChild->text(PWR_COL_INX_CTLMIN).toDouble();
      limitMap.insert(name,limit);
    }
    insertLimit(itemChild,limitMap);
  }
}

QTreeWidgetItem *PowerTreeManage::findItemByName(QTreeWidgetItem *item,QString &targetName)
{

  QTreeWidgetItem *targetItem=NULL;
  if(item->text(PWR_COL_INX_UNIQUENAME)==targetName)
  {
//    qDebug()<<"find target :"<<item->text(0)<<item->text(PWR_COL_INX_UNIQUENAME);
    targetItem=item;
  }
  else
  {
    targetItem=findItemByNameRecursion(item,targetName);
  }
  return targetItem;
}

QTreeWidgetItem *PowerTreeManage::findItemByNameRecursion(QTreeWidgetItem *item,QString &targetName)
{
  static int level;
  QTreeWidgetItem *child;
  QTreeWidgetItem *target=NULL;
  level++;
  for(int i=0;i<item->childCount();i++ )
  {

    child=item->child(i);
//    qDebug()<<tr("%1%2").arg(tr("----------------------------------------------------------").left(level)).arg(child->text(0))<<"finding.......";
    if(child->text(PWR_COL_INX_UNIQUENAME)==targetName)
    {
//      qDebug()<<"find target"<<child->text(0)<<child->text(PWR_COL_INX_UNIQUENAME);
      target=child;
      break;
    }
    target=findItemByNameRecursion(child,targetName);
    if(target!=NULL)
      break;
  }
  level--;
  return target;
}

QString PowerTreeManage::getPath(QTreeWidgetItem *item) {
    QString result = item->text(PWR_COL_INX_NAME);
    QString fileName = item->text(PWR_COL_INX_NAME) + ".ui";
    int count = 0;
    QTreeWidgetItem *currentItem = item;
    while (count < 3) {
        currentItem = currentItem->parent();
        result = currentItem->text(PWR_COL_INX_NAME) + "/" + result;
        count++;
    }
    result = result + "/" + fileName;
    return result;
}

QString PowerTreeManage::getFilterPath(QTreeWidgetItem *item) {
    QString result = item->text(PWR_COL_INX_NAME);
    int count = 0;
    QTreeWidgetItem *currentItem = item;
    while (count < 3) {
        currentItem = currentItem->parent();
        result = currentItem->text(PWR_COL_INX_NAME) + "/" + result;
        count++;
    }
    result = result + "/filter/";
    return result;
}
