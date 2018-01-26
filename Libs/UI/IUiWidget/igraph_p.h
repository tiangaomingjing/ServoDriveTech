#ifndef IGRAPH_P_H
#define IGRAPH_P_H

#include "iuiwidget_global.h"

class SevDevice;
class QTreeWidget;
class BoxItemMapping;
class IGraph;
class IUIWIDGETSHARED_EXPORT IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraph)
public:
  IGraphPrivate();
  virtual ~IGraphPrivate();
protected:
  IGraph *q_ptr;
  SevDevice *m_dev;
  QTreeWidget *m_treeWidget;
  BoxItemMapping*m_mapping;
  QString m_versionName;
};

#endif // IGRAPH_P_H

