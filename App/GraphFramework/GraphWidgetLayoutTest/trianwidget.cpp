#include "trianwidget.h"
#include <QApplication>
#include <QStyleOption>
#include <QDebug>

TrianWidget::TrianWidget(QWidget *parent) : QWidget(parent)
{
    p2 = parent;
}

TrianWidget::~TrianWidget() {

}

void TrianWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    CombinedWidget *p = static_cast<CombinedWidget*>(p2);
    int height = p->getTrianHeight();
    int mode = p->getMode();
    QColor lineColor = p->lineColor();
    QColor fillColor = p->fillColor();

    int startPoint = p->getStartPoint();
    int endPoint = p->getEndPoint();
    int vertexPos = p->getVertexPos();

    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QPointF points[3];
    switch (mode) {
        case MODE_UP:
            points[0] = QPointF(startPoint, height);
            points[1] = QPointF(vertexPos, 0);
            points[2] = QPointF(endPoint, height);
            break;
        case MODE_DOWN:
            points[0] = QPointF(startPoint, 0);
            points[1] = QPointF(vertexPos, height);
            points[2] = QPointF(endPoint, 0);
            break;
    }

    painter.setPen(QPen(fillColor, 2));
    painter.setBrush(fillColor);
    painter.drawPolygon(points, 3);

    painter.setPen(QPen(lineColor, 2));
    painter.drawPolyline(points, 3);
}

