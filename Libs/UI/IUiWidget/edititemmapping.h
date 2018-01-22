#ifndef EDITITEMMAPPING_H
#define EDITITEMMAPPING_H

#include <QObject>
#include <QHash>

#include "iuiwidgetgdef.h"

class QDoubleSpinBox;
class QTreeWidgetItem;

class EditItemMapping : public QObject
{
  Q_OBJECT
public:
  explicit EditItemMapping(QObject *parent = 0);
  ~EditItemMapping();
  void insertBox2Item(QDoubleSpinBox*box,QTreeWidgetItem*item);
  void insertItem2Box(QTreeWidgetItem*,QDoubleSpinBox*);
  void syncEditText2TreeItem(QObject *obj);
  void syncTreeItem2EditText(QTreeWidgetItem *item);
  void setEditStatusByQueryItem(QTreeWidgetItem *item,UI::StatusEditText sta);

signals:

public slots:
private:
  QHash<QDoubleSpinBox*,QTreeWidgetItem*>m_box2ItemHash;
  QHash<QTreeWidgetItem*,QDoubleSpinBox*>m_item2BoxHash;
};

#endif // EDITITEMMAPPING_H
