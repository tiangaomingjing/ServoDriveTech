#include "igraphvelocity.h"
#include "igraphvelocity_p.h"

IGraphVelocity::IGraphVelocity(QWidget *parent) : IGraphWidget(parent)
{
  d_ptr->q_ptr=this;
}
IGraphVelocity::~IGraphVelocity()
{

}

IGraphVelocity::IGraphVelocity(IGraphVelocityPrivate &d, QWidget *parent):IGraphWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
