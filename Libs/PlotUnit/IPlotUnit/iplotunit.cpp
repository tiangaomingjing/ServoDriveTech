#include "iplotunit.h"
#include "iplotunit_p.h"
#include <QDebug>
#include <QCloseEvent>

IPlotUnit::~IPlotUnit()
{
  delete d_ptr;
  qDebug()<<"IPlotUnit destruct-->";
}

void IPlotUnit::closeEvent(QCloseEvent *event)
{
  Q_D(IPlotUnit);
  d->m_winIsIn=true;
  emit winFloatingChange(d->m_winIsIn);
  qDebug()<<"IPlotUnit closeEvent ---------------------------------------";
  event->ignore();
}

IPlotUnit::IPlotUnit(IPlotUnitPrivate &dd, QWidget *parent):d_ptr(&dd),QWidget(parent)
{
  d_ptr->q_ptr=this;
  setAttribute(Qt::WA_DeleteOnClose,false);
}
