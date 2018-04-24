#include "curvemanager.h"
#include "icurve.h"
#include "gtutils.h"
#include "sdtglobaldef.h"

CurveManager::CurveManager(QObject *parent) : QObject(parent)
{
  //----设置好默认颜色------------
  m_colorDefault.append(QColor(Qt::red));
  m_colorDefault.append(QColor(Qt::green));
  m_colorDefault.append(QColor(Qt::blue));
  m_colorDefault.append(QColor(Qt::black));

  m_colorDefault.append(QColor(255,0,255));
  m_colorDefault.append(QColor(0,170,0));
  m_colorDefault.append(QColor(0,170,255));
  m_colorDefault.append(QColor(170,0,255));
  m_colorDefault.append(QColor(170,0,0));
  m_colorDefault.append(QColor(255,170,127));
}

CurveManager::~CurveManager()
{

}

QList<ICurve *> CurveManager::curveList() const
{
  return m_curveList;
}

void CurveManager::addCurve(ICurve *curve)
{
  m_curveList.append(curve);
}

void CurveManager::removeCurve(ICurve *curve)
{
  m_curveList.removeOne(curve);
  delete curve;
}

void CurveManager::removeCurve(int inx)
{
  if(inx<m_curveList.count())
  {
    ICurve *curve=m_curveList.at(inx);
    m_curveList.removeAt(inx);
    delete curve;
  }
}

void CurveManager::clearCurve()
{
  GT::deepClearList(m_curveList);
}

int CurveManager::varCurveTotalCount()
{
  int num=0;
  ICurve *curve;
  for(int i=0;i<m_curveList.count();i++)
  {
    curve=m_curveList.at(i);
    num+=curve->varInputsKeys().size();
  }
  return num;
}

QColor CurveManager::color(int totalCount) const
{
  return m_colorDefault.at(totalCount%m_colorDefault.size());
}

