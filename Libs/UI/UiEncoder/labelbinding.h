#ifndef LABELBINDING_H
#define LABELBINDING_H

#include <QObject>
#include "idatabinding.h"


class LabelBinding : public IDataBinding
{
  Q_OBJECT
public:
  explicit LabelBinding(QObject *parent = 0);
  ~LabelBinding();
  void syncUiDataToTreeItem()Q_DECL_OVERRIDE;
  void syncTreeItemToUiData()Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // LABELBINDING_H
