#include "labelbinding.h"

#include <QDebug>
#include <QLabel>

LabelBinding::LabelBinding(QObject *parent) : IDataBinding(parent)
{

}

LabelBinding::~LabelBinding()
{

}

void LabelBinding::syncUiDataToTreeItem()
{
  QLabel *label=dynamic_cast<QLabel *>(m_dataObj);
  double value=label->text().toDouble()*m_scale;
  m_treeItem->setText(GT::COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
}
void LabelBinding::syncTreeItemToUiData()
{
  QLabel *label=dynamic_cast<QLabel *>(m_dataObj);
  double value=m_treeItem->text(GT::COL_PAGE_TREE_VALUE).toDouble()/m_scale;
  quint32 ofset=value;
  label->setText(QString::number(ofset));
}
