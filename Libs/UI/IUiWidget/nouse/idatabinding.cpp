#include "idatabinding.h"

IDataBinding::IDataBinding(QObject *parent) : QObject(parent)
{

}

void IDataBinding::bind(QObject *obj,QTreeWidgetItem *item)
{
  m_dataObj=obj;
  m_treeItem=item;
  m_scale=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
}
void IDataBinding::multiBind(QObject *multiObj,QTreeWidget *tree)
{
  m_dataMultiObj=multiObj;
  m_tree=tree;
}
