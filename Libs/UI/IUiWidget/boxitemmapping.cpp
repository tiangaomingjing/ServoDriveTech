#include "boxitemmapping.h"

#include <QDoubleSpinBox>
#include <QTreeWidgetItem>
#include <QDebug>
using namespace UI;

BoxItemMapping::BoxItemMapping(QObject *parent) : QObject(parent)
{

}
BoxItemMapping::~BoxItemMapping()
{
  m_box2ItemHash.clear();
  m_item2BoxHash.clear();

}
void BoxItemMapping::insertBox2Item(QDoubleSpinBox*box,QTreeWidgetItem*item)
{
  m_box2ItemHash.insert(box,item);
}

void BoxItemMapping::insertItem2Box(QTreeWidgetItem*item, QDoubleSpinBox*box)
{
  m_item2BoxHash.insert(item,box);
}

void BoxItemMapping::syncBoxText2Item(QDoubleSpinBox *obj)
{
  qDebug()<<"sync boxtext to itme"<<obj->objectName();
  if(m_box2ItemHash.contains(obj))
  {
    QTreeWidgetItem *item=m_box2ItemHash.value(obj);
    double gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
    double value=obj->value()*gain;
    item->setText(GT::COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
    qDebug()<<"gain "<<gain<<"value"<<value;
  }
}

void BoxItemMapping::syncItem2BoxText(QTreeWidgetItem *item)
{
  if(m_item2BoxHash.contains(item))
  {
    QDoubleSpinBox *box=m_item2BoxHash.value(item);
    double value=item->text(GT::COL_PAGE_TREE_VALUE).toDouble();
    double gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
    box->setValue(value/gain);
  }
}
void BoxItemMapping::syncAllItem2BoxText()
{
  qDebug()<<"m_item2BoxHash.keys() count"<<m_item2BoxHash.keys().count();
  foreach (QTreeWidgetItem *item, m_item2BoxHash.keys()) {
    syncItem2BoxText(item);
    qDebug()<<"syncAllItem2BoxText item="<<item->text(0);
  }

}
QList<QDoubleSpinBox*>BoxItemMapping::boxLists()
{
  return m_box2ItemHash.keys();
}

QList<QTreeWidgetItem *> BoxItemMapping::itemLists()
{
  return m_box2ItemHash.values();
}
QDoubleSpinBox* BoxItemMapping::box(QTreeWidgetItem*item)
{
  if(m_item2BoxHash.contains(item))
    return m_item2BoxHash.value(item);
  else
    return NULL;
}

