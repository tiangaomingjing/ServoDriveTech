#include "acwidget.h"
#include <QColor>
#include <QPainter>
#include <QStyleOption>

ACWidget::ACWidget(QWidget *parent) : QWidget(parent)
{
    m_radiusPercent = 0.04;
    m_lineColor = Qt::black;
    m_fillColor = Qt::white;
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
    return QSize(400, 300);
}

void ACWidget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    m_width = this->width();
    m_height = this->height();
    m_radius = m_width * m_radiusPercent;
}

void ACWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QPainterPath myPath;
    myPath.moveTo(m_width - m_radius, 0);
    myPath.lineTo(m_radius, 0);
    myPath.arcTo(0, 0, 2 * m_radius, 2 * m_radius, 90, 90);
    myPath.lineTo(0, m_height - m_radius);
    myPath.arcTo(0, m_height - 2 * m_radius, 2 * m_radius, 2 * m_radius, 180, 90);
    myPath.lineTo(m_width - m_radius, m_height);
    myPath.arcTo(m_width - 2 * m_radius, m_height - 2 * m_radius, 2 * m_radius, 2 * m_radius, 270, 90);
    myPath.lineTo(m_width, m_radius);
    myPath.arcTo(m_width - 2 * m_radius, 0, 2 * m_radius, 2 * m_radius, 0, 90);

    painter.setPen(QPen(m_lineColor, 2));
    painter.setBrush(m_fillColor);
    painter.drawPath(myPath);
    painter.drawLine(0, m_height * 0.5, m_width, m_height * 0.5);
    painter.drawLine(m_width * 0.5, 0, m_width * 0.5, m_height);

    QPointF points[4];
    points[0] = QPointF(0, m_height * 0.75);
    points[1] = QPointF(m_width * 0.25, m_height * 0.75);
    points[2] = QPointF(m_width * 0.75, m_height * 0.25);
    points[3] = QPointF(m_width, m_height * 0.25);
    painter.drawPolyline(points, 4);
}

void ACWidget::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit clicked();
}
