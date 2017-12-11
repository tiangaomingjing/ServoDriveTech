#ifndef IUIWIDGET_H
#define IUIWIDGET_H

#include "iuiwidget_global.h"
#include <QWidget>
class IUiWidgetPrivate;
class QTreeWidget;
class QStackedWidget;
class IUIWIDGETSHARED_EXPORT IUiWidget:public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IUiWidget)
public:
  explicit IUiWidget(QWidget *parent = 0);
  virtual ~IUiWidget();

  virtual QStackedWidget *getUiStackedWidget(void)=0;
  virtual void setCurrentUiIndex(quint8 index);//设置当前两页中显示的页
  virtual bool init();
  virtual void setTreeWidget(QTreeWidget* tree);
  void setUiIndexs(quint8 axisInx,quint8 pageInx,quint8 sdInx);
protected:
  IUiWidget(IUiWidgetPrivate&d, QWidget *parent=0);
  IUiWidgetPrivate *d_ptr;
};

#endif // IUIWIDGET_H
