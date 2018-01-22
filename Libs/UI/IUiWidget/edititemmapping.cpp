#include "edititemmapping.h"

#include <QDoubleSpinBox>
#include <QTreeWidgetItem>
using namespace UI;

EditItemMapping::EditItemMapping(QObject *parent) : QObject(parent)
{

}
EditItemMapping::~EditItemMapping()
{

}
void EditItemMapping::insertBox2Item(QDoubleSpinBox*box,QTreeWidgetItem*item)
{
  m_box2ItemHash.insert(box,item);
}

void EditItemMapping::insertItem2Box(QTreeWidgetItem*item, QDoubleSpinBox*box)
{
  m_item2BoxHash.insert(item,box);
}

void EditItemMapping::syncBoxText2Item(QDoubleSpinBox *obj)
{
  if(m_box2ItemHash.contains(obj))
  {
    QTreeWidgetItem *item=_box2ItemHash.value(obj);
    double gain=item->text(COL_PAGE_TREE_SCALE).toDouble();
    double value=obj->value()*gain;
    item->setText(COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
  }
}

void EditItemMapping::syncItem2BoxText(QTreeWidgetItem *item)
{

}

void EditItemMapping::setBoxStatusByQueryItem(QTreeWidgetItem *item,StatusEditText sta)
{

}
