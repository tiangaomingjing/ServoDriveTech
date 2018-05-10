#include "curveusrvcmdactivator.h"
#include "icurve.h"
#include "curveusrvcmd.h"

#include <QDebug>

CurveUsrVcmdActivator::CurveUsrVcmdActivator()
{

}

void CurveUsrVcmdActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrVcmd";
  m_iCurve = new CurveUsrVcmd(context);
  m_iCurve->prepare();
}

void CurveUsrVcmdActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrVcmd";
}

