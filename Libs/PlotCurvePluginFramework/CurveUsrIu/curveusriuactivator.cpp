#include "curveusriuactivator.h"
#include "icurve.h"
#include "curveusriu.h"

#include <QDebug>

CurveUsrIuActivator::CurveUsrIuActivator()
{

}

void CurveUsrIuActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrIu";
  m_iCurve = new CurveUsrIu(context);
  m_iCurve->prepare();
}

void CurveUsrIuActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrIu";
}

