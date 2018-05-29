#include "curveusrtqactivator.h"
#include "icurve.h"
#include "curveusrtq.h"

#include <QDebug>

CurveUsrTqActivator::CurveUsrTqActivator()
{

}

void CurveUsrTqActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrTq";
  m_iCurve = new CurveUsrTq(context);
  m_iCurve->prepare();
}

void CurveUsrTqActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrTq";
}

