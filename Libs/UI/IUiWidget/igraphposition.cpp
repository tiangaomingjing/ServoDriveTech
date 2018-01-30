#include "igraphposition.h"
#include "igraphposition_p.h"

IGraphPositionPrivate::IGraphPositionPrivate()
{

}

IGraphPositionPrivate::~IGraphPositionPrivate()
{

}

IGraphPosition::IGraphPosition(QWidget *parent) : IGraphWidget(*(new IGraphPositionPrivate),parent)
{

}
IGraphPosition::~IGraphPosition()
{

}

IGraphPosition::IGraphPosition(IGraphPositionPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
