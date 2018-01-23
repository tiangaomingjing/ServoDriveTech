#include "igraphvelocity.h"
#include "igraphvelocity_p.h"
IGraphVelocityPrivate::IGraphVelocityPrivate()
{

}

IGraphVelocityPrivate::~IGraphVelocityPrivate()
{

}

IGraphVelocity::IGraphVelocity(QWidget *parent) : IGraphWidget(parent),IGraph(*(new IGraphVelocityPrivate),parent)
{

}
IGraphVelocity::~IGraphVelocity()
{

}

IGraphVelocity::IGraphVelocity(IGraphVelocityPrivate &d, QWidget *parent):IGraphWidget(parent),IGraph(d,parent)
{

}
