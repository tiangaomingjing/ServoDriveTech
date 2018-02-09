#ifndef ENCCONFIGBINDING129_H
#define ENCCONFIGBINDING129_H

#include <QObject>
#include "idatabinding.h"

class EncConfigBinding129 : public IDataBinding
{
  Q_OBJECT
public:
  explicit EncConfigBinding129(QObject *parent = 0);
  ~EncConfigBinding129();
  void syncMultiUiDataToTree();
  void syncMultiTreeToUiData();

  //just sync treeitem <-> listWidget
  void syncUiDataToTreeItem();
  void syncTreeItemToUiData();

signals:

public slots:
};

#endif // ENCCONFIGBINDING_H
