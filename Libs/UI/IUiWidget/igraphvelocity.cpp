#include "igraphvelocity.h"
#include "igraphvelocity_p.h"
IGraphVelocityPrivate::IGraphVelocityPrivate()
{

}

IGraphVelocityPrivate::~IGraphVelocityPrivate()
{

}

IGraphVelocity::IGraphVelocity(QWidget *parent) : IGraphWidget(*(new IGraphVelocityPrivate),parent)
{

}
IGraphVelocity::~IGraphVelocity()
{

}

IGraphVelocity::IGraphVelocity(IGraphVelocityPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
