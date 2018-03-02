#ifndef SUMITEMWIDGET_H
#define SUMITEMWIDGET_H

#include <QWidget>
#include "sdtgraphicsitems_global.h"

class SDTGRAPHICSITEMSSHARED_EXPORT SumItemWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
public:
  explicit SumItemWidget(QWidget *parent = 0);
  ~SumItemWidget();

  QSize sizeHint() const Q_DECL_OVERRIDE;

  QColor lineColor() const;
  void setLineColor(const QColor &color);

protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:
  void lineColorChanged(const QColor &color);
public slots:
private:
  QColor m_lineColor;
};

#endif // SUMITEMWIDGET_H
