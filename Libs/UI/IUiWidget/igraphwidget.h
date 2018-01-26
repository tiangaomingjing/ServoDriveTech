#ifndef IGRAPHWIDGET_H
#define IGRAPHWIDGET_H

#include <QGraphicsView>
#include "iuiwidget_global.h"

class IGraphWidgetPrivate;
class IUiWidget;

class IUIWIDGETSHARED_EXPORT IGraphWidget : public QGraphicsView
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphWidget)
public:
  explicit IGraphWidget(QWidget *parent = 0);
  virtual ~IGraphWidget();
  virtual void visit(IUiWidget*uiWidget);

protected:
  virtual void setUiVersionName()=0;
  virtual void visitActive(IUiWidget*uiWidget)=0;
signals:

public slots:
protected:
  IGraphWidget(IGraphWidgetPrivate &dd,QWidget *parent=0);
  IGraphWidgetPrivate *d_ptr;
};

#endif // IGRAPHWIDGET_H
