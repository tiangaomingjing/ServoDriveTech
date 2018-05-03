#include "gtplot.h"
#include "qcpitemhandletag.h"
#include "qcpitemmeasure.h"

#include <QDebug>


GtPlot::GtPlot(QWidget *parent) : QCustomPlot(parent),
  m_horizMea(NULL),
  m_vertiMea(NULL)
{
  setFocusPolicy(Qt::ClickFocus);
  setMouseTracking(true);
  selectionRect()->setBrush(QBrush(QColor(150,150,150,30)));

//  htag = new QCPItemHandleTag(this);

//  htag->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
//  htag->position->setType(QCPItemPosition::ptAxisRectRatio);
//  htag->position->setCoords(0.5, 0); // place position at center/top of axis rect

//  htag->setText("1");
////  textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger
////  textLabel->setSelectedFont(QFont(font().family(), 16));
//  htag->setPen(QPen(Qt::black)); // show black border around text
//  htag->setSelectable(true);

//  vtag = new QCPItemHandleTag(this,QCPItemHandleTag::HANDLE_TAG_TYPE_VERTICAL);

//  vtag->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
//  vtag->position->setType(QCPItemPosition::ptAxisRectRatio);
//  vtag->position->setCoords(1, 0.5); // place position at center/top of axis rect

//  vtag->setText("2");
////  vtag->setFont(QFont(font().family(), 16)); // make font a bit larger
////  vtag->setSelectedFont(QFont(font().family(), 16));
//  vtag->setSelectable(true);

  // add the arrow:
//  QCPItemLine *arrow = new QCPItemLine(this);
//  arrow->start->setParentAnchor(textLabel->bottom);
//  arrow->end->setCoords(4, 1.6); // point to (4, 1.6) in x-y-plot coordinates
//  arrow->setHead(QCPLineEnding::esSpikeArrow);

//  QCPItemLine *arrow2 = new QCPItemLine(this);
//  arrow2->start->setParentAnchor(textLabel->bottom);
//  arrow2->end->setParentAnchorX(arrow2->start);
//  arrow2->end->setType(QCPItemPosition::ptAxisRectRatio);
//  arrow2->end->setCoords(0, 1); // point to (4, 1.6) in x-y-plot coordinates


//  QCPItemStraightLine *line=new QCPItemStraightLine(this);
//  line->setSelectable(true);

//  line->point1->setParentAnchor(textLabel->bottom);
////  line->point1->setType(QCPItemPosition::ptViewportRatio);
//  line->point2->setType(QCPItemPosition::ptAxisRectRatio);
////  line->point1->setCoords(0.5,0);
//  line->point2->setCoords(0.5,1);

  setInteraction(QCP::iSelectItems,true);
  setInteraction(QCP::iMultiSelect,true);
  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
  connect(xAxis, SIGNAL(rangeChanged(QCPRange)), xAxis2, SLOT(setRange(QCPRange)));
  connect(yAxis, SIGNAL(rangeChanged(QCPRange)), yAxis2, SLOT(setRange(QCPRange)));
}

GtPlot::~GtPlot()
{
  qDebug()<<"GtPlot destruct-->";
  if(m_horizMea!=NULL)
    delete m_horizMea;
  if(m_vertiMea!=NULL)
    delete m_vertiMea;
  qDebug()<<"GtPlot destruct done-->";
}

void GtPlot::createHorizMea()
{
  if(m_horizMea==NULL)
  {
    m_horizMea=new QCPItemMeasure(this);
    m_horizMea->initPosition();
    connect(m_horizMea->tag1(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onHorizMeaDataChanged(qreal)));
    connect(m_horizMea->tag2(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onHorizMeaDataChanged(qreal)));
    replot();
  }
}

void GtPlot::createVertiMea()
{
  if(m_vertiMea==NULL)
  {
    m_vertiMea=new QCPItemMeasure(this,QCPItemMeasure::MEASURE_TYPE_VERTICAL);
    m_vertiMea->initPosition();
    connect(m_vertiMea->tag1(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onVertiMeaDataChanged(qreal)));
    connect(m_vertiMea->tag2(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onVertiMeaDataChanged(qreal)));
    replot();
  }
}

void GtPlot::clearHorizMea()
{
  if(m_horizMea!=NULL)
  {
    disconnect(m_horizMea->tag1(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onHorizMeaDataChanged(qreal)));
    disconnect(m_horizMea->tag2(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onHorizMeaDataChanged(qreal)));
//    removeItem(m_horizMea->tag1());
//    removeItem(m_horizMea->tag2());
    delete m_horizMea;
    m_horizMea=NULL;
    replot();
  }
}

void GtPlot::clearVertiMea()
{
  if(m_vertiMea!=NULL)
  {
    disconnect(m_vertiMea->tag1(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onVertiMeaDataChanged(qreal)));
    disconnect(m_vertiMea->tag2(),SIGNAL(currentDataChanged(qreal)),this,SLOT(onVertiMeaDataChanged(qreal)));
//    removeItem(m_vertiMea->tag1());
//    removeItem(m_vertiMea->tag2());
    delete m_vertiMea;
    m_vertiMea=NULL;
    replot();
  }
}


void GtPlot::mousePressEvent(QMouseEvent *event)
{

  qDebug()<<"press-->";
  if((event->button()==Qt::LeftButton)&&(QApplication::keyboardModifiers()==Qt::ControlModifier))
  {
    setSelectionRectMode(QCP::srmZoom);
    qDebug()<<"srmZoom"<<"selectionMode"<<selectionRectMode();
  }
  QCustomPlot::mousePressEvent(event);
}

void GtPlot::mouseReleaseEvent(QMouseEvent *event)
{
  qDebug()<<"release-->";

  QCustomPlot::mouseReleaseEvent(event);
  setSelectionRectMode(QCP::srmNone);
}

void GtPlot::mouseMoveEvent(QMouseEvent *event)
{
//  qDebug()<<"GtPlot-----------"<<event->pos();
  qreal x=xAxis->pixelToCoord(event->pos().x());
  qreal y=yAxis->pixelToCoord(event->pos().y());
  m_mouseCurrentPos.setX(x);
  m_mouseCurrentPos.setY(y);
  emit currentPosChanged(m_mouseCurrentPos);

  QCustomPlot::mouseMoveEvent(event);
}

void GtPlot::onHorizMeaDataChanged(qreal data)
{
  Q_UNUSED(data);
  qreal v1=m_horizMea->tag1()->position->coords().x();
  qreal v2=m_horizMea->tag2()->position->coords().x();
  qreal dv=v2-v1;
  emit horizMeaDataChanged(v1,v2,dv);
}

void GtPlot::onVertiMeaDataChanged(qreal data)
{
  Q_UNUSED(data);
  qreal v1=m_vertiMea->tag1()->position->coords().y();
  qreal v2=m_vertiMea->tag2()->position->coords().y();
  qreal dv=v2-v1;
  emit vertiMeaDataChanged(v1,v2,dv);
}




