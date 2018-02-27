#ifndef WIDGETLAYOUTMAINWINDOW_H
#define WIDGETLAYOUTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class WidgetLayoutMainWindow;
}
class QGraphicsScene;
class QGraphicsView;
class WidgetItem;
class SumItem;
class QGraphicsProxyWidget;
class ArrowItem;

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
  QGraphicsView *view;
  WidgetItem *pid;
  SumItem *sumItem;

  WidgetItem *sumWidget;
  WidgetItem *currentFeedback;
  WidgetItem *aheadFeed;
  ArrowItem *arrow;
  ArrowItem *arrowFeedback;
  ArrowItem *arrowAhead;
};

#endif // WIDGETLAYOUTMAINWINDOW_H
