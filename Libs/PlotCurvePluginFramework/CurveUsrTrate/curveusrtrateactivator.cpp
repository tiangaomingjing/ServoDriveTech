#include "curveusrtrateactivator.h"
#include "icurve.h"
#include "curveusrtrate.h"

#include <QDebug>

CurveUsrTrateActivator::CurveUsrTrateActivator()
{

}

void CurveUsrTrateActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrTrate";
  m_iCurve = new CurveUsrTrate(context);
  m_iCurve->prepare();
}

void CurveUsrTrateActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrTrate";
}

