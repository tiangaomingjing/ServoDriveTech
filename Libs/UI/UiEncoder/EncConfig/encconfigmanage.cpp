#include "encconfigmanage.h"
#include "iencconfigitem.h"
#include "sdtglobaldef.h"
#include  <QDebug>

EncConfigManage::EncConfigManage(QObject *parent) : QObject(parent)
{

}
EncConfigManage::~EncConfigManage()
{
  GT::deepClearList(m_encItemList);
}

void EncConfigManage::addEncConfigItem(IEncConfigItem *encItem)
{
  m_encItemList.append(encItem);
}
IEncConfigItem *EncConfigManage::encConfigItem(quint8 index)
{
  if(index<m_encItemList.count())
    return m_encItemList.at(index);
  else
    return NULL;
}

QStringList EncConfigManage::itemNames()
{
  QStringList list;
  for(int i=0;i<m_encItemList.count();i++)
  {
    list.append(m_encItemList.at(i)->objectName());
  }
  qDebug()<<"itemNames"<<list;
  return list;
}

void EncConfigManage::clearAllEncConfigItem()
{
  GT::deepClearList(m_encItemList);
}
