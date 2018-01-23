#include "graphbrake.h"
#include "graphbrake_p.h"

GraphBrake::GraphBrake(QWidget *parent) : QWidget(parent),
  d_ptr(new GraphBrakePrivate)
{
  d_ptr->q_ptr=this;
}
GraphBrake::~GraphBrake()
{

}

GraphBrake::GraphBrake(GraphBrakePrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}

