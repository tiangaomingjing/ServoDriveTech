#include "igraphstatus.h"
#include "igraphstatus_p.h"
IGraphStatusPrivate::IGraphStatusPrivate()
{

}

IGraphStatusPrivate::~IGraphStatusPrivate()
{

}

IGraphStatus::IGraphStatus(QWidget *parent) : IGraph(*(new IGraphStatusPrivate),parent)
{

}
IGraphStatus::~IGraphStatus()
{

}

IGraphStatus::IGraphStatus(IGraphStatusPrivate &dd, QWidget *parent):IGraph(dd,parent)
{

}
