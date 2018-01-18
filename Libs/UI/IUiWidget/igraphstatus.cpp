#include "igraphstatus.h"
#include "igraphstatus_p.h"

IGraphStatus::IGraphStatus(QWidget *parent) : QWidget(parent)
{
  d_ptr->q_ptr=this;
}

IGraphStatus::IGraphStatus(IGraphStatusPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
