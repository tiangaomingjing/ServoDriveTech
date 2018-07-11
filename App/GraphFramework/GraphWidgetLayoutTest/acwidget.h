﻿#ifndef ACWIDGET_H
#define ACWIDGET_H

#include <QWidget>


class ACWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
public:
    explicit ACWidget(QWidget *parent = 0);
    ~ACWidget();
    void setRadiusPercent(double percent);
    double getRadiusPercent();
    QColor lineColor() const;
    QColor fillColor() const;
    void setLineColor(const QColor &color);
    void setFillColor(const QColor &color);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event);
    QSize sizeHint() const Q_DECL_OVERRIDE;
signals:
    void lineColorChanged(const QColor &color);
    void fillColorChanged(const QColor &color);
    void clicked();
public slots:
private:
    int m_width;
    int m_height;
    double m_radiusPercent;
    int m_radius;
    QColor m_lineColor;
    QColor m_fillColor;
};

#endif // ACWIDGET_H
