#ifndef TARGETITEMWIDGET_H
#define TARGETITEMWIDGET_H

#include <QWidget>
#include "sdtgraphicsitems_global.h"

class SDTGRAPHICSITEMSSHARED_EXPORT TargetItemWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor NOTIFY penColorChanged)
public:
  explicit TargetItemWidget(QWidget *parent = 0);
  ~TargetItemWidget();

  QSize sizeHint() const Q_DECL_OVERRIDE;

  QColor penColor() const;
  void setPenColor(const QColor &penColor);

signals:
  void penColorChanged(const QColor &color);
public slots:

protected:
  void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
  QColor m_penColor;
};

#endif // TARGETITEMWIDGET_H
