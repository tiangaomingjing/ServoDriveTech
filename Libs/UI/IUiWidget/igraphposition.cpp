#include "igraphposition.h"
#include "igraphposition_p.h"

IGraphPositionPrivate::IGraphPositionPrivate()
{

}

IGraphPositionPrivate::~IGraphPositionPrivate()
{

}

IGraphPosition::IGraphPosition(QWidget *parent) : IGraphWidget(parent),IGraph(*(new IGraphPositionPrivate),parent)
{

}
IGraphPosition::~IGraphPosition()
{

}

IGraphPosition::IGraphPosition(IGraphPositionPrivate &d, QWidget *parent):IGraphWidget(parent),IGraph(d,parent)
{

}
