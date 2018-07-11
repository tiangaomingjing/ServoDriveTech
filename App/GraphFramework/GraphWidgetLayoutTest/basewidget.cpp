#include "basewidget.h"
#include <QApplication>
#include <QStyleOption>
#include <QDebug>
#include <QPainterPath>

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
{
    p2 = parent;
}

BaseWidget::~BaseWidget() {

}

void BaseWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    CombinedWidget *p = static_cast<CombinedWidget*>(p2);
    int width = p->width();
    int height = p->getBaseHeight();
    int radius = p->getRadius();
    int mode = p->getMode();
    int startPoint = p->getStartPoint();
    int endPoint = p->getEndPoint();
    QColor lineColor = p->lineColor();
    QColor fillColor = p->fillColor();

    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    QPainterPath myPath;
    switch (mode) {
        case MODE_UP:
            myPath.moveTo(startPoint, 0);
            myPath.lineTo(radius, 0);
            myPath.arcTo(0, 0, 2 * radius, 2 * radius, 90, 90);
            myPath.lineTo(0, height - radius);
            myPath.arcTo(0, height - 2 * radius, 2 * radius, 2 * radius, 180, 90);
            myPath.lineTo(width - radius, height);
            myPath.arcTo(width - 2 * radius, height - 2 * radius, 2 * radius, 2 * radius, 270, 90);
            myPath.lineTo(width, radius);
            myPath.arcTo(width - 2 * radius, 0, 2 * radius, 2 * radius, 0, 90);
            myPath.lineTo(endPoint, 0);
            break;
        case MODE_DOWN:
            myPath.moveTo(endPoint, height);
            myPath.lineTo(width - radius, height);
            myPath.arcTo(width - 2 * radius, height - 2 * radius, 2 * radius, 2 * radius, 270, 90);
            myPath.lineTo(width, radius);
            myPath.arcTo(width - 2 * radius, 0, 2 * radius, 2 * radius, 0, 90);
            myPath.lineTo(radius, 0);
            myPath.arcTo(0, 0, 2 * radius, 2 * radius, 90, 90);
            myPath.lineTo(0, height - radius);
            myPath.arcTo(0, height - 2 * radius, 2 * radius, 2 * radius, 180, 90);
            myPath.lineTo(startPoint, height);
    }

    painter.setPen(QPen(lineColor, 2));
    painter.setBrush(fillColor);
    painter.drawPath(myPath);
}

