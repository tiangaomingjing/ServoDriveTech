#ifndef TRIANWIDGET_H
#define TRIANWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include "combinedwidget.h"

class TrianWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrianWidget(QWidget *parent = 0);
    ~TrianWidget();

    QColor lineColor() const;
    QColor fillColor() const;

    void setLineColor(const QColor &color);
    void setFillColor(const QColor &color);
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void lineColorChanged(const QColor &color);
    void fillColorChanged(const QColor &color);
public slots:
private:
    QWidget *p2;
    int m_width;
    int m_height;
};

#endif // TRIANWIDGET_H
