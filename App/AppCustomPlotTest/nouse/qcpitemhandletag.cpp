#include "qcpitemhandletag.h"

#include <QDebug>

QCPItemHandleTag::QCPItemHandleTag(QCustomPlot *parentPlot,HandleTagType type):QCPItemText(parentPlot),
  m_textColor(Qt::white),
  m_textSelectColor(Qt::white),
  m_backgroundColor(qRgb(192,192,192)),
  m_backgroundSelectColor(qRgb(72,72,72)),
  m_type(type),
  m_currentData(0)
{
  if(m_type==HANDLE_TAG_TYPE_HORIZONTAL)//水平标签
  {
    setPadding(QMargins(4,1,4,1));
  }
  else//垂直标签
  {
    setPadding(QMargins(1,0,20,0));
  }

  mSelectedFont.setPointSize(14);
  mFont.setPointSize(14);
}

QCPItemHandleTag::~QCPItemHandleTag()
{
//qDebug()<<"QCPItemHandleTag destruct-->";
}

void QCPItemHandleTag::draw(QCPPainter *painter)
{
  double clipPad = mainPen().widthF();
  QPointF pos(position->pixelPosition());
  QTransform transform = painter->transform();
  transform.translate(pos.x(), pos.y());

  if (!qFuzzyIsNull(mRotation))
    transform.rotate(mRotation);
  painter->setFont(mainFont());
  QRect textRect = painter->fontMetrics().boundingRect(0, 0, 0, 0, Qt::TextDontClip|mTextAlignment, mText);
  QRect textBoxRect = textRect.adjusted(-mPadding.left(), -mPadding.top(), mPadding.right(), mPadding.bottom());
  QPointF textPos = getTextDrawPoint(QPointF(0, 0), textBoxRect, mPositionAlignment); // 0, 0 because the transform does the translation
  textRect.moveTopLeft(textPos.toPoint()+QPoint(mPadding.left(), mPadding.top()));
  textBoxRect.moveTopLeft(textPos.toPoint());

  QRect boundingRect = textBoxRect.adjusted(-clipPad, -clipPad, clipPad, clipPad);
  if (transform.mapRect(boundingRect).intersects(painter->transform().mapRect(clipRect())))
  {
    setColorStyle();
    painter->setTransform(transform);

    painter->setPen(mainPen());
    painter->setBrush(mainBrush());
    QPoint topLeft,topRight,bottomLeft,bottomRight,middle;
    topLeft=textBoxRect.topLeft();
    topRight=textBoxRect.topRight();
    bottomLeft=textBoxRect.bottomLeft();
    bottomRight=textBoxRect.bottomRight();

    QPolygon polygon;

    if(m_type==HANDLE_TAG_TYPE_HORIZONTAL)
    {
      middle=bottomLeft+QPoint(textBoxRect.width()/2,textBoxRect.height()/2);
      polygon<<topLeft<<bottomLeft<<middle<<bottomRight<<topRight;
    }
    else
    {
      middle=topLeft+QPoint(-1*textBoxRect.width()/2,textBoxRect.height()/2);
      polygon<<middle<<topLeft<<topRight<<bottomRight<<bottomLeft;
    }
//    qDebug()<<"polygon"<<polygon;
    painter->drawPolygon(polygon);

    QPointF lineP0=middle;
    QPointF lineP1;
    if(m_type==HANDLE_TAG_TYPE_HORIZONTAL)
      lineP1=middle+QPointF(0,position->axisRect()->height());
    else
      lineP1=middle-QPointF(position->axisRect()->width(),0);

    QLineF line(lineP0,lineP1);
    painter->drawLine(line);

    painter->setPen(QPen(mainColor()));
    painter->drawText(textRect, Qt::TextDontClip|mTextAlignment, mText);


//    qDebug()<<"textRect "<<textRect;
//    qDebug()<<"textBoxRect"<<textBoxRect;
  }
}

void QCPItemHandleTag::mousePressEvent(QMouseEvent *event, const QVariant &details)
{
  Q_UNUSED(details);
  if(m_type==HANDLE_TAG_TYPE_HORIZONTAL)//水平标签
  {
    position->setTypeX(QCPItemPosition::ptPlotCoords);
    position->setTypeY(QCPItemPosition::ptAxisRectRatio);
  }
  else//垂直标签
  {
    position->setTypeX(QCPItemPosition::ptAxisRectRatio);
    position->setTypeY(QCPItemPosition::ptPlotCoords);
  }
  parentPlot()->setInteraction(QCP::iRangeDrag,false);
//  QCPItemText::mousePressEvent(event,details);
  event->accept();
}

void QCPItemHandleTag::mouseMoveEvent(QMouseEvent *event, const QPointF &startPos)
{
  Q_UNUSED(startPos);
  double data;
  if(m_type==HANDLE_TAG_TYPE_HORIZONTAL)
  {
    data=parentPlot()->xAxis->pixelToCoord(event->pos().x());
    position->setCoords(data,0);
  }
  else
  {
    data=parentPlot()->yAxis->pixelToCoord(event->pos().y());
    position->setCoords(1,data);
  }
  m_currentData=data;
  emit currentDataChanged(m_currentData);

  parentPlot()->setCursor(QCursor(Qt::PointingHandCursor));
  parentPlot()->replot();
//  qDebug()<<"event pos"<<event->pos()<<"data="<<data;
  event->accept();
//  QCPItemText::mouseMoveEvent(event,startPos);

}

void QCPItemHandleTag::mouseReleaseEvent(QMouseEvent *event, const QPointF &startPos)
{
  Q_UNUSED(startPos);
//  qDebug()<<"Release startPos"<<startPos;
  parentPlot()->setCursor(QCursor(Qt::ArrowCursor));
  parentPlot()->setInteraction(QCP::iRangeDrag,true);
  event->accept();
  //  QCPItemText::mouseReleaseEvent(event,startPos);
}

void QCPItemHandleTag::setColorStyle()
{
  QPen p;
  setSelectedColor(m_textSelectColor);
  setColor(m_textColor);
  setSelectedBrush(QBrush(m_backgroundSelectColor));
  setBrush(QBrush(m_backgroundColor));
  setSelectedPen(QPen(m_backgroundSelectColor));
  p.setColor(m_backgroundColor);
  p.setStyle(Qt::DashLine);
  setPen(p);
}

qreal QCPItemHandleTag::currentData() const
{
  return m_currentData;
}

void QCPItemHandleTag::setCurrentData(qreal data)
{
  m_currentData=data;
}


QColor QCPItemHandleTag::backgroundSelectColor() const
{
  return m_backgroundSelectColor;
}

void QCPItemHandleTag::setBackgroundSelectColor(const QColor &backgroundSelectColor)
{
  if(m_backgroundSelectColor != backgroundSelectColor)
  {
    m_backgroundSelectColor = backgroundSelectColor;
    emit backgroundSelectColorChanged(m_backgroundSelectColor);
  }
}

QColor QCPItemHandleTag::backgroundColor() const
{
  return m_backgroundColor;
}

void QCPItemHandleTag::setBackgroundColor(const QColor &backgroundColor)
{
  if(m_backgroundColor != backgroundColor)
  {
    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged(m_backgroundColor);
  }
}

QColor QCPItemHandleTag::textSelectColor() const
{
  return m_textSelectColor;
}

void QCPItemHandleTag::setTextSelectColor(const QColor &textSelectColor)
{
  if(m_textSelectColor != textSelectColor)
  {
    m_textSelectColor = textSelectColor;
    emit textSelectColorChanged(m_textSelectColor);
  }
}

QColor QCPItemHandleTag::textColor() const
{
  return m_textColor;
}

void QCPItemHandleTag::setTextColor(const QColor &textColor)
{
  if(m_textColor != textColor)
  {
    m_textColor = textColor;
    emit textColorChanged(m_textColor);
  }
}

