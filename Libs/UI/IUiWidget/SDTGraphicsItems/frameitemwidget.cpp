#include "frameitemwidget.h"
#include <QPainter>
#include <QStyleOption>

FrameItemWidget::FrameItemWidget(QWidget *parent) : QWidget(parent)
{
    m_wPercent = 0.25;
    m_hPercent = 0.25;
    m_posPercent = 0.5;
    m_vertexPercent = 0.5;
    m_radiusPercent = 0.04;
    m_lineColor = Qt::black;
    m_fillColor = Qt::white;
    m_mode = 0;
}

FrameItemWidget::~FrameItemWidget() {

}


void FrameItemWidget::setWPercent(double percent) {
    m_wPercent = percent;
}

void FrameItemWidget::setHPercent(double percent) {
    m_hPercent = percent;
}

void FrameItemWidget::setPosPercent(double percent) {
    m_posPercent = percent;
}

void FrameItemWidget::setMode(int mode) {
    m_mode = mode;
}

int FrameItemWidget::getMode() {
    return m_mode;
}

double FrameItemWidget::getWPercent() {
    return m_wPercent;
}

double FrameItemWidget::getHPercent() {
    return m_hPercent;
}

double FrameItemWidget::getPosPercent() {
    return m_posPercent;
}

double FrameItemWidget::getVertexPercent() {
    return m_vertexPercent;
}

double FrameItemWidget::getRadiusPercent() {
    return m_radiusPercent;
}

QColor FrameItemWidget::lineColor() const
{
    return m_lineColor;
}

void FrameItemWidget::setLineColor(const QColor &color)
{
    if(m_lineColor != color)
    {
        m_lineColor = color;
        emit lineColorChanged(m_lineColor);
    }
}

QColor FrameItemWidget::fillColor() const
{
    return m_fillColor;
}

void FrameItemWidget::setFillColor(const QColor &color)
{
    if(m_fillColor != color)
    {
        m_fillColor = color;
        emit fillColorChanged(m_fillColor);
    }
}

int FrameItemWidget::getRadius() {
    return m_radius;
}

void FrameItemWidget::setVertexPercent(double percent) {
    m_vertexPercent = percent;
}

void FrameItemWidget::setRadiusPercent(double percent) {
    m_radiusPercent = percent;
}

int FrameItemWidget::getTrianHeight() {
    return m_trianHeight;
}

int FrameItemWidget::getBaseHeight() {
    return m_baseHeight;
}

int FrameItemWidget::getVertexPos() {
    return m_vertexPos;
}

int FrameItemWidget::getStartPoint() {
    return m_startPoint;
}

int FrameItemWidget::getEndPoint() {
    return m_endPoint;
}

void FrameItemWidget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    m_radius = this->width() * m_radiusPercent;
    m_trianHeight = this->height() * m_hPercent;
    m_baseHeight = this->height() - m_trianHeight;
    m_trianPos = this->width() * m_posPercent;
    m_halfTrianWidth = this->width() * m_wPercent / 2.0;
    m_vertexPos = this->width() * m_vertexPercent;
    m_startPoint = m_trianPos - m_halfTrianWidth;
    if (m_trianPos - m_halfTrianWidth < m_radius) {
        m_startPoint = m_radius;
    }
    m_endPoint = m_trianPos + m_halfTrianWidth;
    if (m_trianPos + m_halfTrianWidth > this->width() - m_radius) {
        m_endPoint = this->width() - m_radius;
    }
}

QSize FrameItemWidget::sizeHint() const {
    return QSize(200, 150);
}

void FrameItemWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    int height = this->height();
    int width = this->width();
    QPainterPath myPath;
    painter.setPen(QPen(m_lineColor, 2));
    painter.setBrush(m_fillColor);
    double adjust=painter.pen().width()/2;
    switch (m_mode) {
        case 0:
            myPath.moveTo(m_vertexPos, 0);
            myPath.lineTo(m_startPoint, m_trianHeight);
            myPath.lineTo(m_radius+adjust, m_trianHeight);
            myPath.arcTo(adjust, m_trianHeight, 2 * m_radius, 2 * m_radius, 90, 90);
            myPath.lineTo(adjust, height - m_radius-adjust);
            myPath.arcTo(adjust, height - 2 * m_radius-adjust, 2 * m_radius, 2 * m_radius, 180, 90);
            myPath.lineTo(width - m_radius-adjust, height-adjust);
            myPath.arcTo(width - 2 * m_radius-adjust, height - 2 * m_radius-adjust, 2 * m_radius, 2 * m_radius, 270, 90);
            myPath.lineTo(width-adjust, m_radius + m_trianHeight);
            myPath.arcTo(width - 2 * m_radius-adjust, m_trianHeight, 2 * m_radius, 2 * m_radius, 0, 90);
            myPath.lineTo(m_endPoint, m_trianHeight);
            myPath.lineTo(m_vertexPos, 0);
            break;
        case 1:
            myPath.moveTo(m_vertexPos, height);
            myPath.lineTo(m_endPoint, m_baseHeight);
            myPath.lineTo(width - m_radius-adjust, m_baseHeight);
            myPath.arcTo(width - 2 * m_radius-adjust, m_baseHeight - 2 * m_radius, 2 * m_radius, 2 * m_radius, 270, 90);
            myPath.lineTo(width-adjust, m_radius+adjust);
            myPath.arcTo(width - 2 * m_radius-adjust, adjust, 2 * m_radius, 2 * m_radius, 0, 90);
            myPath.lineTo(m_radius+adjust, 0+adjust);
            myPath.arcTo(adjust, adjust, 2 * m_radius, 2 * m_radius, 90, 90);
            myPath.lineTo(adjust, m_baseHeight - m_radius);
            myPath.arcTo(adjust, m_baseHeight - 2 * m_radius, 2 * m_radius, 2 * m_radius, 180, 90);
            myPath.lineTo(m_startPoint, m_baseHeight);
            myPath.lineTo(m_vertexPos, height);
            break;
    }

    painter.drawPath(myPath);
}

