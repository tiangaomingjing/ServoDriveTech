#include "curveusrposactivator.h"
#include "icurve.h"
#include "curveusrpos.h"

#include <QDebug>

CurveUsrPosActivator::CurveUsrPosActivator()
{

}

void CurveUsrPosActivator::start(ctkPluginContext *context)
{
  qDebug()<<"activator start   new CurveUsrPos";
  m_iCurve = new CurveUsrPos(context);
  m_iCurve->prepare();
}

void CurveUsrPosActivator::stop(ctkPluginContext *context)
{
  Q_UNUSED(context);
  if(m_iCurve!=NULL)
  {
    delete m_iCurve;
    m_iCurve=NULL;
  }
  qDebug()<<"activator stop delete CurveUsrPos";
}

