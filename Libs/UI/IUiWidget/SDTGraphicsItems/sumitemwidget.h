#ifndef SUMITEMWIDGET_H
#define SUMITEMWIDGET_H

#include <QWidget>
#include "sdtgraphicsitems_global.h"

class SDTGRAPHICSITEMSSHARED_EXPORT SumItemWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
  Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
public:
  explicit SumItemWidget(QWidget *parent = 0);
  ~SumItemWidget();

  QSize sizeHint() const Q_DECL_OVERRIDE;

  QColor lineColor() const;
  void setLineColor(const QColor &color);

  QColor fillColor() const;
  void setFillColor(const QColor &fillColor);

protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:
  void lineColorChanged(const QColor &color);
  void fillColorChanged(const QColor &color);
public slots:
private:
  QColor m_lineColor;
  QColor m_fillColor;
};

#endif // SUMITEMWIDGET_H
