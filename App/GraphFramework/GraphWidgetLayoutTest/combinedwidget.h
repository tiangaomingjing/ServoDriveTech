#ifndef COMBINEDWIDGET_H
#define COMBINEDWIDGET_H

#include <QWidget>
#include <QColor>
#include <QSize>
#include "trianwidget.h"
#include "basewidget.h"

enum LayoutMode
{
  MODE_UP = 0,
  MODE_DOWN = 1,
};
class QVBoxLayout;

class CombinedWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
public:
    explicit CombinedWidget(QWidget *parent = 0);
    ~CombinedWidget();

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
public:
    QWidget *m_base;

signals:
    void lineColorChanged(const QColor &color);
    void fillColorChanged(const QColor &color);
public slots:
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
private:
    QWidget *m_trian;
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
    QVBoxLayout *m_vBox;
};

#endif // COMBINEDWIDGET_H
