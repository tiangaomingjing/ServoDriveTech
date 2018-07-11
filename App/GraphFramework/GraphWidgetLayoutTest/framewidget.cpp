#include "framewidget.h"
#include <QPainter>
#include <QStyleOption>

FrameWidget::FrameWidget(QWidget *parent) : QWidget(parent)
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

FrameWidget::~FrameWidget() {

}


void FrameWidget::setWPercent(double percent) {
    m_wPercent = percent;
}

void FrameWidget::setHPercent(double percent) {
    m_hPercent = percent;
}

void FrameWidget::setPosPercent(double percent) {
    m_posPercent = percent;
}

void FrameWidget::setMode(int mode) {
    m_mode = mode;
}

int FrameWidget::getMode() {
    return m_mode;
}

double FrameWidget::getWPercent() {
    return m_wPercent;
}

double FrameWidget::getHPercent() {
    return m_hPercent;
}

double FrameWidget::getPosPercent() {
    return m_posPercent;
}

double FrameWidget::getVertexPercent() {
    return m_vertexPercent;
}

double FrameWidget::getRadiusPercent() {
    return m_radiusPercent;
}

QColor FrameWidget::lineColor() const
{
    return m_lineColor;
}

void FrameWidget::setLineColor(const QColor &color)
{
    if(m_lineColor != color)
    {
        m_lineColor = color;
        emit lineColorChanged(m_lineColor);
    }
}

QColor FrameWidget::fillColor() const
{
    return m_fillColor;
}

void FrameWidget::setFillColor(const QColor &color)
{
    if(m_fillColor != color)
    {
        m_fillColor = color;
        emit fillColorChanged(m_fillColor);
    }
}

int FrameWidget::getRadius() {
    return m_radius;
}

void FrameWidget::setVertexPercent(double percent) {
    m_vertexPercent = percent;
}

void FrameWidget::setRadiusPercent(double percent) {
    m_radiusPercent = percent;
}

int FrameWidget::getTrianHeight() {
    return m_trianHeight;
}

int FrameWidget::getBaseHeight() {
    return m_baseHeight;
}

int FrameWidget::getVertexPos() {
    return m_vertexPos;
}

int FrameWidget::getStartPoint() {
    return m_startPoint;
}

int FrameWidget::getEndPoint() {
    return m_endPoint;
}

void FrameWidget::resizeEvent(QResizeEvent *event) {
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

QSize FrameWidget::sizeHint() const {
    return QSize(400, 300);
}

void FrameWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    int height = this->height();
    int width = this->width();
    QPainterPath myPath;
    switch (m_mode) {
        case 0:
            myPath.moveTo(m_vertexPos, 0);
            myPath.lineTo(m_startPoint, m_trianHeight);
            myPath.lineTo(m_radius, m_trianHeight);
            myPath.arcTo(0, m_trianHeight, 2 * m_radius, 2 * m_radius, 90, 90);
            myPath.lineTo(0, height - m_radius);
            myPath.arcTo(0, height - 2 * m_radius, 2 * m_radius, 2 * m_radius, 180, 90);
            myPath.lineTo(width - m_radius, height);
            myPath.arcTo(width - 2 * m_radius, height - 2 * m_radius, 2 * m_radius, 2 * m_radius, 270, 90);
            myPath.lineTo(width, m_radius + m_trianHeight);
            myPath.arcTo(width - 2 * m_radius, m_trianHeight, 2 * m_radius, 2 * m_radius, 0, 90);
            myPath.lineTo(m_endPoint, m_trianHeight);
            myPath.lineTo(m_vertexPos, 0);
            break;
        case 1:
            myPath.moveTo(m_vertexPos, height);
            myPath.lineTo(m_endPoint, m_baseHeight);
            myPath.lineTo(width - m_radius, m_baseHeight);
            myPath.arcTo(width - 2 * m_radius, m_baseHeight - 2 * m_radius, 2 * m_radius, 2 * m_radius, 270, 90);
            myPath.lineTo(width, m_radius);
            myPath.arcTo(width - 2 * m_radius, 0, 2 * m_radius, 2 * m_radius, 0, 90);
            myPath.lineTo(m_radius, 0);
            myPath.arcTo(0, 0, 2 * m_radius, 2 * m_radius, 90, 90);
            myPath.lineTo(0, m_baseHeight - m_radius);
            myPath.arcTo(0, m_baseHeight - 2 * m_radius, 2 * m_radius, 2 * m_radius, 180, 90);
            myPath.lineTo(m_startPoint, m_baseHeight);
            myPath.lineTo(m_vertexPos, height);
            break;
    }

    painter.setPen(QPen(m_lineColor, 2));
    painter.setBrush(m_fillColor);
    painter.drawPath(myPath);
}

