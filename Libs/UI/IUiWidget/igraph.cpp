#include "igraph.h"
#include "igraph_p.h"
#include "boxitemmapping.h"

IGraphPrivate::IGraphPrivate():
  m_dev(NULL),
  m_treeWidget(NULL),
  m_mapping(new BoxItemMapping)
{

}

IGraphPrivate::~IGraphPrivate()
{
  delete m_mapping;
}

IGraph::IGraph(QWidget *parent) : QWidget(parent),
  d_ptr(new IGraphPrivate)
{
  d_ptr->q_ptr=this;
}
IGraph::~IGraph()
{
  delete d_ptr;
}
IGraph::IGraph(IGraphPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
