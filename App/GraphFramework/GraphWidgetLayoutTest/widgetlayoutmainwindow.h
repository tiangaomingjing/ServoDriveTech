#ifndef WIDGETLAYOUTMAINWINDOW_H
#define WIDGETLAYOUTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class WidgetLayoutMainWindow;
}
class QGraphicsScene;
class InteractiveView;
class WidgetItem;
class SumItem;
class QGraphicsProxyWidget;
class ArrowItem;
class AnchorItemHelper;

class WidgetLayoutMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit WidgetLayoutMainWindow(QWidget *parent = 0);
  ~WidgetLayoutMainWindow();

private slots:
  void on_actionSetfont_triggered();
  void onSliderValueChanged(int value);
  void onActionTest();

private:
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

  void adjustItemPostion();


private:
  Ui::WidgetLayoutMainWindow *ui;

  QGraphicsScene *scene;
//  QGraphicsView *view;
  InteractiveView *view;
  WidgetItem *u0;
  WidgetItem *u1;
  WidgetItem *u2;
  WidgetItem *u3;


  WidgetItem *t4;


  WidgetItem *t1;
  WidgetItem *t2;
  WidgetItem *t3;
  ArrowItem *a1;
  ArrowItem *a2;
  ArrowItem *a3;
  ArrowItem *a4;
  ArrowItem *a5;
  ArrowItem *a6;
  ArrowItem *a7;
  ArrowItem *a8;

  AnchorItemHelper *anchorHelper;
};

#endif // WIDGETLAYOUTMAINWINDOW_H
