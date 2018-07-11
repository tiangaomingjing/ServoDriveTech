#include "linenumberbinding.h"
#include<QSpinBox>
#include<QTreeWidgetItem>

LineNumberBinding::LineNumberBinding(QObject *parent) : IDataBinding(parent)
{

}
LineNumberBinding::~LineNumberBinding()
{

}

void LineNumberBinding::syncUiDataToTreeItem()
{
  QSpinBox *box=qobject_cast<QSpinBox *>(m_dataObj);
  double value=box->value()*m_scale;
  m_treeItem->setText(GT::COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
}

void LineNumberBinding::syncTreeItemToUiData()
{
  QSpinBox *box=qobject_cast<QSpinBox *>(m_dataObj);
  double value=m_treeItem->text(GT::COL_PAGE_TREE_VALUE).toDouble()/m_scale;
  box->setValue((int)value);
}
