#include "curveusricmdactivator.h"
#include "icurve.h"
#include "curveusricmd.h"

#include <QDebug>

CurveUsrIcmdActivator::CurveUsrIcmdActivator()
{

}

void CurveUsrIcmdActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrIcmd";
  m_iCurve = new CurveUsrIcmd(context);
  m_iCurve->prepare();
}

void CurveUsrIcmdActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrIcmd";
}

