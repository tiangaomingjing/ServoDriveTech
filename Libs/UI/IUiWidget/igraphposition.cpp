#include "igraphposition.h"
#include "igraphposition_p.h"
#include "boxitemmapping.h"

IGraphPositionPrivate::IGraphPositionPrivate()
{

}

IGraphPositionPrivate::~IGraphPositionPrivate()
{

}


IGraphPosition::~IGraphPosition()
{

}

void IGraphPosition::syncTreeDataToUiFace()
{
  Q_D(IGraphPosition);
  d->m_mapping->syncAllItem2BoxText();
}

void IGraphPosition::createItems()
{

}

void IGraphPosition::setDoubleSpinBoxConnections()
{

}

void IGraphPosition::installDoubleSpinBoxEventFilter()
{

}

void IGraphPosition::adjustPosition()
{

}


IGraphPosition::IGraphPosition(IGraphPositionPrivate &dd, QWidget *parent):IGraphWidget(dd,parent)
{

}
