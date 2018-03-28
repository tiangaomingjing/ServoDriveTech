#ifndef IGRAPH_P_H
#define IGRAPH_P_H

#include "igraph.h"
#include "boxitemmapping.h"

class SevDevice;
class QTreeWidget;
class BoxItemMapping;
class IGraph;
class IUiWidget;
class IGraphPrivate
{
  Q_DECLARE_PUBLIC(IGraph)
public:
  IGraphPrivate() :
    m_dev(NULL),
    m_treeWidget(NULL),
    m_mapping(new BoxItemMapping)
  {

  }

  virtual ~IGraphPrivate()
  {
    delete m_mapping;
  }

protected:
  IGraph *q_ptr;
  SevDevice *m_dev;
  QTreeWidget *m_treeWidget;
  BoxItemMapping*m_mapping;
  QString m_versionName;
  IUiWidget *m_uiWidget;
};

#endif // IGRAPH_P_H

