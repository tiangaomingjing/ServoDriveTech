#include "curveusrvffdactivator.h"
#include "icurve.h"
#include "curveusrvffd.h"

#include <QDebug>

CurveUsrVffdActivator::CurveUsrVffdActivator()
{

}

void CurveUsrVffdActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrVffd";
  m_iCurve = new CurveUsrVffd(context);
  m_iCurve->prepare();
}

void CurveUsrVffdActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrVffd";
}

