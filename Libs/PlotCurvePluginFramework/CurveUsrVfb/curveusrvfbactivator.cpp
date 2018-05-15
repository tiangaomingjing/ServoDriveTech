#include "curveusrvfbactivator.h"
#include "icurve.h"
#include "curveusrvfb.h"

#include <QDebug>

CurveUsrVfbActivator::CurveUsrVfbActivator()
{

}

void CurveUsrVfbActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrVfb";
  m_iCurve = new CurveUsrVfb(context);
  m_iCurve->prepare();
}

void CurveUsrVfbActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrVfb";
}

