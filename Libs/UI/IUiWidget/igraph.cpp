#include "igraph.h"
#include "igraph_p.h"

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
