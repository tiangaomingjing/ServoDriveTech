#ifndef LINENUMBERBINDING_H
#define LINENUMBERBINDING_H

#include <QObject>
#include "idatabinding.h"

class LineNumberBinding : public IDataBinding
{
  Q_OBJECT
public:
  explicit LineNumberBinding(QObject *parent = 0);
  ~LineNumberBinding();
  void syncUiDataToTreeItem();
  void syncTreeItemToUiData();
signals:

public slots:
};

#endif // LINENUMBERBINDING_H
