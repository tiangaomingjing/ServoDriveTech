﻿#include "igraphposition.h"
#include "igraphposition_p.h"
IGraphPosition::IGraphPosition(QWidget *parent) : QWidget(parent)
{
  d_ptr->q_ptr=this;
}

IGraphPosition::IGraphPosition(IGraphPositionPrivate &d, QWidget *parent):QWidget(parent),d_ptr(&d)
{
  d_ptr->q_ptr=this;
}
