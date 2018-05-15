#include "curveusrifbactivator.h"
#include "icurve.h"
#include "curveusrifb.h"

#include <QDebug>

CurveUsrIfbActivator::CurveUsrIfbActivator()
{

}

void CurveUsrIfbActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrIfb";
  m_iCurve = new CurveUsrIfb(context);
  m_iCurve->prepare();
}

void CurveUsrIfbActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrIfb";
}

