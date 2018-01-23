#include "igraphcurrent.h"
#include "igraphcurrent_p.h"
IGraphCurrentPrivate::IGraphCurrentPrivate()
{

}

IGraphCurrentPrivate::~IGraphCurrentPrivate()
{

}


IGraphCurrent::IGraphCurrent(QWidget *parent) : IGraphWidget(parent),IGraph(*(new IGraphCurrentPrivate),parent)
{

}
IGraphCurrent::~IGraphCurrent()
{

}

IGraphCurrent::IGraphCurrent(IGraphCurrentPrivate &d, QWidget *parent):IGraphWidget(parent),IGraph(d,parent)
{

}
