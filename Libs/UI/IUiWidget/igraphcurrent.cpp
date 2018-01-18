#include "igraphcurrent.h"
#include "igraphcurrent_p.h"

IGraphCurrent::IGraphCurrent(QWidget *parent) : QWidget(parent)
{
  d_ptr->q_ptr=this;
}
IGraphCurrent::IGraphCurrent(IGraphCurrentPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
