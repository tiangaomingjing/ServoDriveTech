#include "iplotunit.h"
#include "iplotunit_p.h"


IPlotUnit::~IPlotUnit()
{
  delete d_ptr;
}

IPlotUnit::IPlotUnit(IPlotUnitPrivate &dd, QWidget *parent):d_ptr(&dd),QWidget(parent)
{
  d_ptr->q_ptr=this;
}
