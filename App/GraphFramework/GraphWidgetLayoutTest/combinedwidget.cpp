#include "combinedwidget.h"
#include <QVBoxLayout>
#include <QDebug>

CombinedWidget::CombinedWidget(QWidget *parent) : QWidget(parent)
{
    m_wPercent = 0.25;
    m_hPercent = 0.25;
    m_posPercent = 0.5;
    m_vertexPercent = 0.5;
    m_radiusPercent = 0.04;
    m_lineColor = Qt::black;
    m_fillColor = Qt::white;
    m_mode = 0;

    m_base = new BaseWidget(this);
    m_trian = new TrianWidget(this);
    vBox = new QVBoxLayout;
    switch (m_mode) {
    case MODE_UP:
        vBox->addWidget(m_trian);
        vBox->addWidget(m_base);
        break;
    case MODE_DOWN:
        vBox->addWidget(m_base);
        vBox->addWidget(m_trian);
        break;
    }
    vBox->setSpacing(0);
    vBox->setMargin(0);
    this->setLayout(vBox);
}

CombinedWidget::~CombinedWidget() {
    delete m_base;
    delete m_trian;
    delete vBox;
}


void CombinedWidget::setWPercent(double percent) {
    m_wPercent = percent;
}

void CombinedWidget::setHPercent(double percent) {
    m_hPercent = percent;
}

void CombinedWidget::setPosPercent(double percent) {
    m_posPercent = percent;
}

void CombinedWidget::setMode(int mode) {
    m_mode = mode;
}

int CombinedWidget::getMode() {
    return m_mode;
}

double CombinedWidget::getWPercent() {
    return m_wPercent;
}

double CombinedWidget::getHPercent() {
    return m_hPercent;
}

double CombinedWidget::getPosPercent() {
    return m_posPercent;
}

double CombinedWidget::getVertexPercent() {
    return m_vertexPercent;
}

double CombinedWidget::getRadiusPercent() {
    return m_radiusPercent;
}

QColor CombinedWidget::lineColor() const
{
    return m_lineColor;
}

void CombinedWidget::setLineColor(const QColor &color)
{
    if(m_lineColor != color)
    {
        m_lineColor = color;
        emit lineColorChanged(m_lineColor);
    }
}

QColor CombinedWidget::fillColor() const
{
    return m_fillColor;
}

void CombinedWidget::setFillColor(const QColor &color)
{
    if(m_fillColor != color)
    {
        m_fillColor = color;
        emit fillColorChanged(m_fillColor);
    }
}

int CombinedWidget::getRadius() {
    return m_radius;
}

void CombinedWidget::setVertexPercent(double percent) {
    m_vertexPercent = percent;
}

void CombinedWidget::setRadiusPercent(double percent) {
    m_radiusPercent = percent;
}

int CombinedWidget::getTrianHeight() {
    return m_trianHeight;
}

int CombinedWidget::getBaseHeight() {
    return m_baseHeight;
}

int CombinedWidget::getVertexPos() {
    return m_vertexPos;
}

int CombinedWidget::getStartPoint() {
    return m_startPoint;
}

int CombinedWidget::getEndPoint() {
    return m_endPoint;
}

void CombinedWidget::resizeEvent(QResizeEvent *event) {
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
    vBox->setStretchFactor(m_trian, m_trianHeight);
    vBox->setStretchFactor(m_base, m_baseHeight);
}

QSize CombinedWidget::sizeHint() const {
    return QSize(400, 300);
}
