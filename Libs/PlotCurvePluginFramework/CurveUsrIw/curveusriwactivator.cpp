#include "curveusriwactivator.h"
#include "icurve.h"
#include "curveusriw.h"

#include <QDebug>

CurveUsrIwActivator::CurveUsrIwActivator()
{

}

void CurveUsrIwActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrIw";
  m_iCurve = new CurveUsrIw(context);
  m_iCurve->prepare();
}

void CurveUsrIwActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrIw";
}

