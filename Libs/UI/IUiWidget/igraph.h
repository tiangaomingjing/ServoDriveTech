#ifndef IGRAPH_H
#define IGRAPH_H

#include <QWidget>
#include "iuiwidget_global.h"

class IUiWidget;
class IGraphPrivate;
class QDoubleSpinBox;
class QTreeWidgetItem;

class IUIWIDGETSHARED_EXPORT IGraph:public QWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(IGraph)
public:
  //抽象基类，不存在构造的函数，因为其不能创建实例，只能是指针引用
  virtual ~IGraph();
  virtual void visit(IUiWidget*uiWidget);
  virtual void syncTreeDataToUiFace();

protected:
  virtual void setUiVersionName()=0;
  virtual void setCustomVisitActive(IUiWidget*uiWidget)=0;
  virtual void setupDataMappings()=0;

  virtual void setEditTextStatus(QDoubleSpinBox *box,int status);
  virtual void setEditTextStatusDefaultAll();

  virtual void setDoubleSpinBoxConnections();
  virtual void installDoubleSpinBoxEventFilter();
  virtual bool eventFilter(QObject *obj, QEvent *event);

  virtual void setCommonConnections();

signals:

protected slots:
  virtual void onItemBoxEditTextError(QTreeWidgetItem *item,int status);
  virtual void onFaceCssChanged(const QString &css);
  virtual void onDoubleSpinBoxFocusOut();
protected:
  IGraph(IGraphPrivate&dd,QWidget *parent=0);
  IGraphPrivate *d_ptr;

};

#endif // IGRAPH_H
