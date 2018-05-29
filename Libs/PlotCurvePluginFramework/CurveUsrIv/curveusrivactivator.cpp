#include "curveusrivactivator.h"
#include "icurve.h"
#include "curveusriv.h"

#include <QDebug>

CurveUsrIvActivator::CurveUsrIvActivator()
{

}

void CurveUsrIvActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrIv";
  m_iCurve = new CurveUsrIv(context);
  m_iCurve->prepare();
}

void CurveUsrIvActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrIv";
}

