#include "igraphbrake.h"
#include "igraphbrake_p.h"

IGraphBrakePrivate::IGraphBrakePrivate()
{

}

IGraphBrakePrivate:: ~IGraphBrakePrivate()
{

}

IGraphBrake::~IGraphBrake()
{
  //*(new GraphBrakePrivate)这里不做释放，只做在这个GraphBrakePrivate独有的数据new出来的才delete
}

IGraphBrake::IGraphBrake(IGraphBrakePrivate &dd, QWidget *parent):IGraph(dd,parent)
{

}

