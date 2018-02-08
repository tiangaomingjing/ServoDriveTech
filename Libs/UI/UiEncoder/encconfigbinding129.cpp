#include "encconfigbinding129.h"
#include "iencconfigitem.h"
#include <QDebug>

EncConfigBinding129::EncConfigBinding129(QObject *parent) : IDataBinding(parent)
{

}
EncConfigBinding129::~EncConfigBinding129()
{

}
void EncConfigBinding129::syncMultiUiDataToTree()
{
  IEncConfigItem *encItem=dynamic_cast<IEncConfigItem *>(m_dataMultiObj);
  double gain,value;
  QTreeWidgetItem *item;

  //0 coder_typ_3
  qDebug()<<"coder_typ_1";
  item=m_tree->topLevelItem(0);
  gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
  value=(int)encItem->encType()*gain;
  item->setText(GT::COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
  qDebug()<<"coder_typ_3";

  //2 line_num_3
  item=m_tree->topLevelItem(2);
  gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
  value=encItem->lineNumber()*gain;
  item->setText(GT::COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
  qDebug()<<"coder_typ_3";

  //3 ABS_ENC_CFG.all
  item=m_tree->topLevelItem(3);
  gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
  value=encItem->encConfigData()*gain;
  item->setText(GT::COL_PAGE_TREE_VALUE,QString::number(value,'f',3));
  qDebug()<<"coder_typ_3";

}

void EncConfigBinding129::syncMultiTreeToUiData()
{
  IEncConfigItem *encItem=dynamic_cast<IEncConfigItem *>(m_dataMultiObj);
  double gain,value;
  QTreeWidgetItem *item;
  //0 coder_typ_3
  item=m_tree->topLevelItem(0);
  gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
  value=item->text(GT::COL_PAGE_TREE_VALUE).toDouble()/gain;
  int type=(int)value;
  encItem->setEncType((IEncConfigItem::EncType) type);

  //2 line_num_3
  item=m_tree->topLevelItem(2);
  gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
  value=item->text(GT::COL_PAGE_TREE_VALUE).toDouble()/gain;
  encItem->setLineNumber((quint32)value);

  //3 ABS_ENC_CFG.all
  item=m_tree->topLevelItem(3);
  gain=item->text(GT::COL_PAGE_TREE_SCALE).toDouble();
  value=item->text(GT::COL_PAGE_TREE_VALUE).toDouble()/gain;
  encItem->setEncConfigData((quint16)value);
}

