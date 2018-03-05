#ifndef IGRAPHWIDGET_H
#define IGRAPHWIDGET_H

#include "iuiwidget_global.h"
#include "interactiveview.h"

class IGraphWidgetPrivate;
class IUiWidget;

class IUIWIDGETSHARED_EXPORT IGraphWidget : public InteractiveView
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphWidget)
  Q_PROPERTY(QColor backGroundColor READ backGroundColor WRITE setBackGroundColor NOTIFY backGroundColorChanged)
  Q_PROPERTY(QColor arrowColor READ arrowColor WRITE setArrowColor NOTIFY arrowColorChanged)
public:
  explicit IGraphWidget(QWidget *parent = 0);
  virtual ~IGraphWidget();
  virtual void visit(IUiWidget*uiWidget);

  QColor backGroundColor() const;
  void setBackGroundColor(const QColor &color);
  QColor arrowColor() const;
  void setArrowColor(const QColor &color);

  void setCustumBackgroundColor();

protected:
  virtual void setUiVersionName()=0;
  virtual void visitActive(IUiWidget*uiWidget)=0;
signals:
  void backGroundColorChanged(const QColor &color);
  void arrowColorChanged(const QColor &color );
public slots:
protected:
  IGraphWidget(IGraphWidgetPrivate &dd,QWidget *parent=0);
  IGraphWidgetPrivate *d_ptr;
};

#endif // IGRAPHWIDGET_H
