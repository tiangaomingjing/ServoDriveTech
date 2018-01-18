#include "igraphpower.h"
#include "igraphpower_p.h"

IGraphPower::IGraphPower(QWidget *parent) : QWidget(parent)
{
  d_ptr->q_ptr=this;
}

IGraphPower::IGraphPower(IGraphPowerPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
