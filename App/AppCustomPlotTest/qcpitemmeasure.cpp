#include "qcpitemmeasure.h"
#include "qcustomplot.h"
#include "qcpitemhandletag.h"

QCPItemMeasure::QCPItemMeasure(QCustomPlot *parentPlot,MeasureType type ,QObject *parent ) : QObject(parent),
  m_type(type),
  m_parentPlot(parentPlot)
{
  if(m_type==MEASURE_TYPE_HORIZONTAL)
  {
    m_tag1 = new QCPItemHandleTag(m_parentPlot);
    m_tag1->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_tag1->position->setType(QCPItemPosition::ptAxisRectRatio);
    m_tag1->position->setCoords(0.45, 0); // place position at center/top of axis rect
    m_tag1->setText("1");
    m_tag1->setSelectable(true);

    m_tag2 = new QCPItemHandleTag(m_parentPlot);
    m_tag2->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_tag2->position->setType(QCPItemPosition::ptAxisRectRatio);
    m_tag2->position->setCoords(0.55, 0); // place position at center/top of axis rect
    m_tag2->setText("2");
    m_tag2->setSelectable(true);

    //只有m_parentPlot先显示出来，这些数据才正确
    if(m_parentPlot!=NULL)
    {
      qreal data=m_parentPlot->xAxis->pixelToCoord(m_tag1->position->pixelPosition().x());
      m_tag1->setCurrentData(data);
      data=m_parentPlot->xAxis->pixelToCoord(m_tag2->position->pixelPosition().x());
      m_tag2->setCurrentData(data);
    }

  }
  else
  {
    m_tag1 = new QCPItemHandleTag(m_parentPlot,QCPItemHandleTag::HANDLE_TAG_TYPE_VERTICAL);
    m_tag1->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_tag1->position->setType(QCPItemPosition::ptAxisRectRatio);
    m_tag1->position->setCoords(1, 0.45); // place position at center/top of axis rect
    m_tag1->setText("1");
    m_tag1->setSelectable(true);

    m_tag2 = new QCPItemHandleTag(m_parentPlot,QCPItemHandleTag::HANDLE_TAG_TYPE_VERTICAL);
    m_tag2->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_tag2->position->setType(QCPItemPosition::ptAxisRectRatio);
    m_tag2->position->setCoords(1, 0.55); // place position at center/top of axis rect
    m_tag2->setText("2");
    m_tag2->setSelectable(true);

    if(m_parentPlot!=NULL)
    {
      qreal data=m_parentPlot->xAxis->pixelToCoord(m_tag1->position->pixelPosition().y());
      m_tag1->setCurrentData(data);
      data=m_parentPlot->xAxis->pixelToCoord(m_tag2->position->pixelPosition().y());
      m_tag2->setCurrentData(data);
    }
  }

  qDebug()<<"x"<<m_parentPlot->xAxis->pixelToCoord(m_tag1->position->pixelPosition().x());
  qDebug()<<"y"<<m_parentPlot->xAxis->pixelToCoord(m_tag1->position->pixelPosition().y());
  qDebug()<<"x"<<m_parentPlot->xAxis->pixelToCoord(m_tag2->position->pixelPosition().x());
  qDebug()<<"y"<<m_parentPlot->xAxis->pixelToCoord(m_tag2->position->pixelPosition().y());
}

QCPItemMeasure::~QCPItemMeasure()
{
  delete m_tag1;
  delete m_tag2;
}

void QCPItemMeasure::setMeasureScale(qreal scale)
{
  m_scale=scale;
}

qreal QCPItemMeasure::tag1MeasureData()
{
  return m_tag1->currentData();
}

qreal QCPItemMeasure::tag2MeasureData()
{
  return m_tag2->currentData();
}

