#include "qcpitemmeasure.h"
#include "qcustomplot.h"
#include "qcpitemhandletag.h"

QCPItemMeasure::QCPItemMeasure(QCustomPlot *parentPlot,MeasureType type ,QObject *parent ) : QObject(parent),
  m_type(type),
  m_parentPlot(parentPlot),
  m_selectState(SELECT_STATE_NONE),
  m_dv(0)
{
  if(m_type==MEASURE_TYPE_HORIZONTAL)
  {
    m_tag1 = new QCPItemHandleTag(m_parentPlot);
    m_tag1->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
//    m_tag1->position->setType(QCPItemPosition::ptAxisRectRatio);
//    m_tag1->position->setCoords(0.45, 0); // place position at center/top of axis rect
    m_tag1->setText("1");
    m_tag1->setSelectable(true);

    m_tag2 = new QCPItemHandleTag(m_parentPlot);
    m_tag2->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
//    m_tag2->position->setType(QCPItemPosition::ptAxisRectRatio);
//    m_tag2->position->setCoords(0.55, 0); // place position at center/top of axis rect
    m_tag2->setText("2");
    m_tag2->setSelectable(true);

    //只有m_parentPlot先显示出来，这些数据才正确
    if(m_parentPlot!=NULL&&m_parentPlot->isVisible())
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
//    m_tag1->position->setType(QCPItemPosition::ptAxisRectRatio);
//    m_tag1->position->setCoords(1, 0.45); // place position at center/top of axis rect
    m_tag1->setText("1");
    m_tag1->setSelectable(true);

    m_tag2 = new QCPItemHandleTag(m_parentPlot,QCPItemHandleTag::HANDLE_TAG_TYPE_VERTICAL);
    m_tag2->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
//    m_tag2->position->setType(QCPItemPosition::ptAxisRectRatio);
//    m_tag2->position->setCoords(1, 0.55); // place position at center/top of axis rect
    m_tag2->setText("2");
    m_tag2->setSelectable(true);

    if(m_parentPlot!=NULL&&m_parentPlot->isVisible())
    {
      qreal data=m_parentPlot->xAxis->pixelToCoord(m_tag1->position->pixelPosition().y());
      m_tag1->setCurrentData(data);
      data=m_parentPlot->xAxis->pixelToCoord(m_tag2->position->pixelPosition().y());
      m_tag2->setCurrentData(data);
    }
  }

  connect(m_tag1,SIGNAL(selectionChanged(bool)),this,SLOT(onTagSelectChanged()));
  connect(m_tag2,SIGNAL(selectionChanged(bool)),this,SLOT(onTagSelectChanged()));
  connect(m_tag1,SIGNAL(currentDataChanged(qreal)),this,SLOT(onTag1DataChanged(qreal)));
  connect(m_tag2,SIGNAL(currentDataChanged(qreal)),this,SLOT(onTag2DataChanged(qreal)));

  if(m_parentPlot!=NULL&&m_parentPlot->isVisible())
  {
    qDebug()<<"x"<<m_parentPlot->xAxis->pixelToCoord(m_tag1->position->pixelPosition().x());
    qDebug()<<"y"<<m_parentPlot->xAxis->pixelToCoord(m_tag1->position->pixelPosition().y());
    qDebug()<<"x"<<m_parentPlot->xAxis->pixelToCoord(m_tag2->position->pixelPosition().x());
    qDebug()<<"y"<<m_parentPlot->xAxis->pixelToCoord(m_tag2->position->pixelPosition().y());
  }
}

QCPItemMeasure::~QCPItemMeasure()
{
//  qDebug()<<"QCPItemMeasure destruct-->";
  if(m_parentPlot!=NULL)
  {
    disconnect(m_tag1,SIGNAL(selectionChanged(bool)),this,SLOT(onTagSelectChanged()));
    disconnect(m_tag2,SIGNAL(selectionChanged(bool)),this,SLOT(onTagSelectChanged()));
    disconnect(m_tag1,SIGNAL(currentDataChanged(qreal)),this,SLOT(onTag1DataChanged(qreal)));
    disconnect(m_tag2,SIGNAL(currentDataChanged(qreal)),this,SLOT(onTag2DataChanged(qreal)));
    m_parentPlot->removeItem(m_tag1);
    m_parentPlot->removeItem(m_tag2);
  }
//  delete m_tag1;//这两个的生命已经交给了 m_parentPlot
  //  delete m_tag2;
}

void QCPItemMeasure::initPosition()
{
  m_tag1->position->setType(QCPItemPosition::ptAxisRectRatio);
  m_tag2->position->setType(QCPItemPosition::ptAxisRectRatio);
  if(m_type==MEASURE_TYPE_HORIZONTAL)
  {
    m_tag1->position->setCoords(0.45, 0);
    m_tag2->position->setCoords(0.55, 0);
    m_parentPlot->replot();

    m_tag1->position->setTypeX(QCPItemPosition::ptPlotCoords);
    m_tag1->position->setTypeY(QCPItemPosition::ptAxisRectRatio);
    m_tag2->position->setTypeX(QCPItemPosition::ptPlotCoords);
    m_tag2->position->setTypeY(QCPItemPosition::ptAxisRectRatio);

    m_dv=m_tag2->position->coords().x()-m_tag1->position->coords().x();
  }
  else
  {
    m_tag1->position->setCoords(1, 0.55);
    m_tag2->position->setCoords(1, 0.45);
    m_parentPlot->replot();

    m_tag1->position->setTypeY(QCPItemPosition::ptPlotCoords);
    m_tag1->position->setTypeX(QCPItemPosition::ptAxisRectRatio);
    m_tag2->position->setTypeY(QCPItemPosition::ptPlotCoords);
    m_tag2->position->setTypeX(QCPItemPosition::ptAxisRectRatio);

    m_dv=m_tag2->position->coords().y()-m_tag1->position->coords().y();
  }
  m_parentPlot->replot();
  qDebug()<<"dv"<<m_dv;
}


qreal QCPItemMeasure::tag1MeasureData() const
{
  qreal data=0;
  if(m_type==MEASURE_TYPE_HORIZONTAL)
    data=m_tag1->position->coords().x();
  else
    data=m_tag1->position->coords().y();
  return data;
}

qreal QCPItemMeasure::tag2MeasureData() const
{
  qreal data=0;
  if(m_type==MEASURE_TYPE_HORIZONTAL)
    data=m_tag2->position->coords().x();
  else
    data=m_tag2->position->coords().y();
  return data;
}

qreal QCPItemMeasure::dTagMeasureData() const
{
  return tag2MeasureData()-tag1MeasureData();
}

QCPItemHandleTag *QCPItemMeasure::tag1() const
{
  return m_tag1;
}

QCPItemHandleTag *QCPItemMeasure::tag2() const
{
  return m_tag2;
}

void QCPItemMeasure::onTagSelectChanged()
{
  //selectBit[0] 标志m_tag1 , selectBit[1] 标志m_tag2
  quint8 selectBit=0x00;
  if(m_tag1->selected())
    selectBit|=0x01;
  if(m_tag2->selected())
    selectBit|=0x02;

  switch(selectBit)
  {
  case 0:
    m_selectState=SELECT_STATE_NONE;
    break;
  case 1:
  case 2:
    m_selectState=SELECT_STATE_SINGLE;
    break;
  case 3:
    m_selectState=SELECT_STATE_ALL;
    break;
  }
  qDebug()<<"m_selectState "<<m_selectState;

}

void QCPItemMeasure::onTag1DataChanged(qreal data)
{
  if(m_selectState==SELECT_STATE_ALL)
  {
    if(m_type==MEASURE_TYPE_HORIZONTAL)
      m_tag2->position->setCoords(m_dv+data,0);
    else
      m_tag2->position->setCoords(1,m_dv+data);
  }
  else
  {
    if(m_type==MEASURE_TYPE_HORIZONTAL)
      m_dv=m_tag2->position->coords().x()-data;
    else
      m_dv=m_tag2->position->coords().y()-data;
    qDebug()<<"dv"<<m_dv;
  }
}

void QCPItemMeasure::onTag2DataChanged(qreal data)
{
  if(m_selectState==SELECT_STATE_ALL)
  {
    if(m_type==MEASURE_TYPE_HORIZONTAL)
      m_tag1->position->setCoords(data-m_dv,0);
    else
      m_tag1->position->setCoords(1,data-m_dv);
  }
  else
  {
    if(m_type==MEASURE_TYPE_HORIZONTAL)
      m_dv=data-m_tag1->position->coords().x();
    else
      m_dv=data-m_tag1->position->coords().y();
    qDebug()<<"dv"<<m_dv;
  }
}

