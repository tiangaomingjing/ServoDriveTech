#include "igraphbrake.h"
#include "igraphbrake_p.h"

IGraphBrake::IGraphBrake(QWidget *parent) : QWidget(parent),
  d_ptr(new IGraphBrakePrivate)
{
  d_ptr->q_ptr=this;
}
IGraphBrake::~IGraphBrake()
{

}

IGraphBrake::IGraphBrake(IGraphBrakePrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}

