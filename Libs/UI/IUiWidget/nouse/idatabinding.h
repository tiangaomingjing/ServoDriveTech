#ifndef IDATABINDING_H
#define IDATABINDING_H

#include <QObject>
#include "iuiwidget_global.h"
#include "sdtglobaldef.h"

#include<QTreeWidgetItem>
#include<QTreeWidget>

class IUIWIDGETSHARED_EXPORT IDataBinding : public QObject
{
  Q_OBJECT
public:
  explicit IDataBinding(QObject *parent = 0);
  virtual ~IDataBinding(){}
  void bind(QObject *obj,QTreeWidgetItem *item);
  void multiBind(QObject *multiObj,QTreeWidget *tree);
  virtual void syncUiDataToTreeItem(){}
  virtual void syncTreeItemToUiData(){}

  virtual void syncMultiUiDataToTree(){}
  virtual void syncMultiTreeToUiData(){}

  QObject *dataUiWidget() {return m_dataObj;}
protected:

signals:

public slots:

protected:
  //single
  QTreeWidgetItem *m_treeItem;
  QObject *m_dataObj;
  double m_scale;

  //multi
  QObject *m_dataMultiObj;
  QTreeWidget *m_tree;
};

#endif // IDATABINDING_H
