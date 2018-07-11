#include "acwidget.h"
#include <QColor>
#include <QPainter>
#include <QStyleOption>

#include <QDebug>

ACWidget::ACWidget(QWidget *parent) : QWidget(parent)
{
    m_radiusPercent = 0.2;
    m_lineColor = Qt::white;
    m_fillColor = Qt::blue;
}

ACWidget::~ACWidget() {

}

double ACWidget::getRadiusPercent() {
    return m_radiusPercent;
}

void ACWidget::setRadiusPercent(double percent) {
    m_radiusPercent = percent;
}

QColor ACWidget::lineColor() const
{
    return m_lineColor;
}

void ACWidget::setLineColor(const QColor &color)
{
    if(m_lineColor != color)
    {
        m_lineColor = color;
        emit lineColorChanged(m_lineColor);
    }
}

QColor ACWidget::fillColor() const
{
    return m_fillColor;
}

void ACWidget::setFillColor(const QColor &color)
{
    if(m_fillColor != color)
    {
        m_fillColor = color;
        emit fillColorChanged(m_fillColor);
    }
}

QSize ACWidget::sizeHint() const {
  int w=fontMetrics().width("m")*8;
    return QSize(w, w);
}

void ACWidget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    m_width = this->width();
    m_height = this->height();
    m_radius = m_width * m_radiusPercent;
}

void ACWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
  qDebug()<<"w="<<width()<<"h="<<height();

    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    m_radius=width()*m_radiusPercent;

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

void ACWidget::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit clicked();
  qDebug()<<"clicked";
}
