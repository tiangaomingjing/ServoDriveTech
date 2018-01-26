#include "igraphcurrent.h"
#include "igraphcurrent_p.h"
IGraphCurrentPrivate::IGraphCurrentPrivate()
{

}

IGraphCurrentPrivate::~IGraphCurrentPrivate()
{

}


IGraphCurrent::IGraphCurrent(QWidget *parent) : IGraphWidget(*(new IGraphCurrentPrivate),parent)
{

}
IGraphCurrent::~IGraphCurrent()
{

}

IGraphCurrent::IGraphCurrent(IGraphCurrentPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
