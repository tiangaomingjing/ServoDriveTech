#ifndef LABELITEMWIDGET_H
#define LABELITEMWIDGET_H

#include <QObject>
#include <QLabel>
#include "sdtgraphicsitems_global.h"

class SDTGRAPHICSITEMSSHARED_EXPORT LabelItemWidget : public QLabel
{
  Q_OBJECT
public:
  explicit LabelItemWidget(QWidget *parent=0, Qt::WindowFlags f=0);
  explicit LabelItemWidget(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);
  ~ LabelItemWidget();

protected:
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
signals:
  void clicked();
};

#endif // LABELITEMWIDGET_H
