#ifndef IGRAPHWIDGET_H
#define IGRAPHWIDGET_H

#include "interactiveview.h"
#include "iuiwidget_global.h"

class IGraphWidgetPrivate;
class IUiWidget;
class QDoubleSpinBox;
class QTreeWidgetItem;

class IUIWIDGETSHARED_EXPORT IGraphWidget : public InteractiveView
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraphWidget)
  Q_PROPERTY(QColor backGroundColor READ backGroundColor WRITE setBackGroundColor NOTIFY backGroundColorChanged)
  Q_PROPERTY(QColor arrowColor READ arrowColor WRITE setArrowColor NOTIFY arrowColorChanged)
public:

  virtual ~IGraphWidget();
  virtual void visit(IUiWidget*uiWidget);

  QColor backGroundColor() const;
  void setBackGroundColor(const QColor &color);
  QColor arrowColor() const;
  void setArrowColor(const QColor &color);

  void setCustumBackgroundColor();

  virtual void syncTreeDataToUiFace()=0;

protected:
  virtual void setUiVersionName()=0;
  virtual void createItems()=0;
  virtual void setupDataMappings()=0;
  virtual void installDoubleSpinBoxEventFilter()=0;
  virtual void setDoubleSpinBoxConnections()=0;
  virtual void setCustomVisitActive(IUiWidget*uiWidget)=0;

  virtual void adjustPosition()=0;

  virtual void setEditTextStatus(QDoubleSpinBox *box,int status);
  virtual void setEditTextStatusDefaultAll();

//  virtual bool eventFilter(QObject *obj, QEvent *event);

  void setCommonConnections();

  virtual QPointF pidInitPos() = 0;

signals:
  void backGroundColorChanged(const QColor &color);
  void arrowColorChanged(const QColor &color );

protected slots:
  virtual void onItemBoxEditTextError(QTreeWidgetItem *item,int status);
  virtual void onFaceCssChanged(const QString &css);
  virtual void onDoubleSpinBoxFocusOut();
  virtual void onUIFItemClicked() {}

protected:
  IGraphWidget(IGraphWidgetPrivate &dd,QWidget *parent=0);
  IGraphWidgetPrivate *d_ptr;
};

#endif // IGRAPHWIDGET_H
