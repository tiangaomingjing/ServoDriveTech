#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QWidget>
#include <QColor>
#include <QSize>

class FrameWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)

public:
    explicit FrameWidget(QWidget *parent = 0);
    ~FrameWidget();
    void setWPercent(double percent);
    void setHPercent(double percent);
    void setPosPercent(double percent);
    void setVertexPercent(double percent);
    void setRadiusPercent(double percent);
    void setMode(int mode);

    double getWPercent();
    double getHPercent();
    double getPosPercent();
    double getVertexPercent();
    double getRadiusPercent();
    int getRadius();
    int getTrianHeight();
    int getBaseHeight();
    int getStartPoint();
    int getEndPoint();
    int getVertexPos();
    int getMode();
    QColor lineColor() const;
    QColor fillColor() const;
    void setLineColor(const QColor &color);
    void setFillColor(const QColor &color);

signals:
    void lineColorChanged(const QColor &color);
    void fillColorChanged(const QColor &color);
public slots:
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event);
    QSize sizeHint() const Q_DECL_OVERRIDE;
private:
    int m_mode;
    double m_wPercent;
    double m_hPercent;
    double m_posPercent;
    double m_vertexPercent;
    double m_radiusPercent;
    QColor m_lineColor;
    QColor m_fillColor;
    int m_radius;
    int m_trianHeight;
    int m_baseHeight;
    int m_trianPos;
    int m_halfTrianWidth;
    int m_startPoint;
    int m_endPoint;
    int m_vertexPos;
};

#endif // FRAMEWIDGET_H
