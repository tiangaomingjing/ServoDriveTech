#include "curveusrperractivator.h"
#include "icurve.h"
#include "curveusrperr.h"

#include <QDebug>

CurveUsrPerrActivator::CurveUsrPerrActivator()
{

}

void CurveUsrPerrActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrPerr";
  m_iCurve = new CurveUsrPerr(context);
  m_iCurve->prepare();
}

void CurveUsrPerrActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrPerr";
}

