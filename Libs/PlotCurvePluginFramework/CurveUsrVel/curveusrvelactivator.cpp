#include "curveusrvelactivator.h"
#include "icurve.h"
#include "curveusrvel.h"

#include <QDebug>

CurveUsrVelActivator::CurveUsrVelActivator()
{

}

void CurveUsrVelActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrVel";
  m_iCurve = new CurveUsrVel(context);
  m_iCurve->prepare();
}

void CurveUsrVelActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrVel";
}

