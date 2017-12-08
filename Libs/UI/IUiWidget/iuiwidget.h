#ifndef IUIWIDGET_H
#define IUIWIDGET_H

#include "iuiwidget_global.h"
#include <QWidget>
class IUiWidgetPrivate;
class QTreeWidget;
class IUIWIDGETSHARED_EXPORT IUiWidget:public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IUiWidget)
public:
  explicit IUiWidget(QWidget *parent = 0);
  virtual ~IUiWidget();
  virtual bool init();
  virtual void setTreeWidget(QTreeWidget* tree);
protected:
  IUiWidget(IUiWidgetPrivate&d, QWidget *parent=0);
  IUiWidgetPrivate *d_ptr;
};

#endif // IUIWIDGET_H
