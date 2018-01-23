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
    double gain=item->text(COL_PAGE_TREE_SCALE).toDouble();
    double value=obj->value()*gain;
    item->setText(COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
    qDebug()<<"gain "<<gain<<"value"<<value;
  }
}

void BoxItemMapping::syncItem2BoxText(QTreeWidgetItem *item)
{
  if(m_item2BoxHash.contains(item))
  {
    QDoubleSpinBox *box=m_item2BoxHash.value(item);
    double value=item->text(COL_PAGE_TREE_VALUE).toDouble();
    double gain=item->text(COL_PAGE_TREE_SCALE).toDouble();
    box->setValue(value/gain);
  }
}

void BoxItemMapping::setBoxStatusByQueryItem(QTreeWidgetItem *item,StatusEditText sta)
{

}
