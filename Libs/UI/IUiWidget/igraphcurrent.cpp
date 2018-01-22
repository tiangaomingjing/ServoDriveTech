#include "igraphcurrent.h"
#include "igraphcurrent_p.h"

IGraphCurrent::IGraphCurrent(QWidget *parent) : IGraphWidget(parent)
{
  d_ptr->q_ptr=this;
}
IGraphCurrent::~IGraphCurrent()
{

}

IGraphCurrent::IGraphCurrent(IGraphCurrentPrivate &d, QWidget *parent):IGraphWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
