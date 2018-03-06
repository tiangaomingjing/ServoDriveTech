#ifndef EDITITEMMAPPING_H
#define EDITITEMMAPPING_H

#include <QObject>
#include <QHash>

#include "iuiwidgetgdef.h"
#include "iuiwidget_global.h"

class QDoubleSpinBox;
class QTreeWidgetItem;

class IUIWIDGETSHARED_EXPORT BoxItemMapping : public QObject
{
  Q_OBJECT
public:
  explicit BoxItemMapping(QObject *parent = 0);
  ~BoxItemMapping();
  void insertBox2Item(QDoubleSpinBox*box,QTreeWidgetItem*item);
  void insertItem2Box(QTreeWidgetItem*item,QDoubleSpinBox*box);
  void insertBox2MultiItem(QDoubleSpinBox*box,QTreeWidgetItem*item);
  void syncBoxText2Item(QDoubleSpinBox *obj);
  void syncItem2BoxText(QTreeWidgetItem *item);
  void syncBoxText2MultiItem(QDoubleSpinBox *obj);
  void syncAllItem2BoxText();
  QList<QDoubleSpinBox*>boxLists();
  QList<QTreeWidgetItem*>itemLists();
  QDoubleSpinBox* box(QTreeWidgetItem*item);
  QTreeWidgetItem* item(QDoubleSpinBox *box);

signals:

public slots:
private:
  QHash<QDoubleSpinBox*,QTreeWidgetItem*>m_box2ItemHash;
  QHash<QTreeWidgetItem*,QDoubleSpinBox*>m_item2BoxHash;
  QMultiHash<QDoubleSpinBox*,QTreeWidgetItem*>m_box2MultiItemHash;
};

#endif // EDITITEMMAPPING_H
