#include "curverawactivator.h"
#include "icurve.h"
#include "curveraw.h"

#include <QDebug>

CurveRawActivator::CurveRawActivator()
{

}

void CurveRawActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveRaw";
  m_iCurve = new CurveRaw(context);
  m_iCurve->prepare();
}

void CurveRawActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveRaw";
}

