#include "igraphvelocity.h"
#include "igraphvelocity_p.h"
#include "boxitemmapping.h"

IGraphVelocityPrivate::IGraphVelocityPrivate()
{

}

IGraphVelocityPrivate::~IGraphVelocityPrivate()
{

}

IGraphVelocity::~IGraphVelocity()
{

}

void IGraphVelocity::syncTreeDataToUiFace()
{
  Q_D(IGraphVelocity);
  d->m_mapping->syncAllItem2BoxText();
}

void IGraphVelocity::createItems()
{

}

void IGraphVelocity::setDoubleSpinBoxConnections()
{

}

void IGraphVelocity::installDoubleSpinBoxEventFilter()
{

}

void IGraphVelocity::adjustPosition()
{

}


IGraphVelocity::IGraphVelocity(IGraphVelocityPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
