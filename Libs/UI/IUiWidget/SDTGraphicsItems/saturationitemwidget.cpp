#include "saturationitemwidget.h"
#include <QColor>
#include <QPainter>
#include <QStyleOption>

#include <QDebug>

SaturationItemWidget::SaturationItemWidget(QWidget *parent) : QWidget(parent)
{
    m_radiusPercent = 0.2;
    m_lineColor = Qt::white;
    m_fillColor = Qt::blue;
}

SaturationItemWidget::~SaturationItemWidget() {

}

double SaturationItemWidget::getRadiusPercent() {
    return m_radiusPercent;
}

void SaturationItemWidget::setRadiusPercent(double percent) {
    m_radiusPercent = percent;
}

QColor SaturationItemWidget::lineColor() const
{
    return m_lineColor;
}

void SaturationItemWidget::setLineColor(const QColor &color)
{
    if(m_lineColor != color)
    {
        m_lineColor = color;
        emit lineColorChanged(m_lineColor);
    }
}

QColor SaturationItemWidget::fillColor() const
{
    return m_fillColor;
}

void SaturationItemWidget::setFillColor(const QColor &color)
{
    if(m_fillColor != color)
    {
        m_fillColor = color;
        emit fillColorChanged(m_fillColor);
    }
}

QSize SaturationItemWidget::sizeHint() const {
  int w=fontMetrics().width("m")*6;
    return QSize(w, w);
}

void SaturationItemWidget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    m_width = this->width();
    m_height = this->height();
    m_radius = m_width * m_radiusPercent;
}

void SaturationItemWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
//  qDebug()<<"w="<<width()<<"h="<<height();

    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    m_radius=width()*m_radiusPercent;
    setMinimumHeight(width());

    QPen myPen;
    myPen.setColor(m_lineColor);
    myPen.setWidth(2);
    painter.setPen(myPen);
    painter.setBrush(QBrush(m_fillColor));

    double adjust=myPen.width()/2;

    QPainterPath myPath;
    myPath.moveTo(m_width - m_radius-adjust, adjust);
    myPath.lineTo(m_radius+adjust, adjust);
    myPath.arcTo(adjust, adjust, 2 * m_radius, 2 * m_radius, 90, 90);
    myPath.lineTo(adjust, m_height - m_radius-adjust);
    myPath.arcTo(adjust, m_height - 2 * m_radius-adjust, 2 * m_radius, 2 * m_radius, 180, 90);
    myPath.lineTo(m_width - m_radius-adjust, m_height-adjust);
    myPath.arcTo(m_width - 2 * m_radius-adjust, m_height - 2 * m_radius-adjust, 2 * m_radius, 2 * m_radius, 270, 90);
    myPath.lineTo(m_width-adjust, m_radius+adjust);
    myPath.arcTo(m_width - 2 * m_radius-adjust, adjust, 2 * m_radius, 2 * m_radius, 0, 90);

    painter.drawPath(myPath);
    painter.drawLine(adjust, m_height * 0.5, m_width-adjust, m_height * 0.5);
    painter.drawLine(m_width * 0.5, adjust, m_width * 0.5, m_height-adjust);

    QPointF points[4];
    points[0] = QPointF(adjust, m_height * 0.75);
    points[1] = QPointF(m_width * 0.25+adjust, m_height * 0.75);
    points[2] = QPointF(m_width * 0.75, m_height * 0.25);
    points[3] = QPointF(m_width-adjust, m_height * 0.25);
    painter.drawPolyline(points, 4);

}

void SaturationItemWidget::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit clicked();
  qDebug()<<"clicked";
}
