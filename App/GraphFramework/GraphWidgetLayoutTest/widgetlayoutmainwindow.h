#ifndef WIDGETLAYOUTMAINWINDOW_H
#define WIDGETLAYOUTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class WidgetLayoutMainWindow;
}
class QGraphicsScene;
class QGraphicsView;
class PidItem;
class SumItem;
class QGraphicsProxyWidget;

class WidgetLayoutMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit WidgetLayoutMainWindow(QWidget *parent = 0);
  ~WidgetLayoutMainWindow();

private slots:
  void on_actionSetfont_triggered();
  void onSliderValueChanged(int value);

private:
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

  void adjustItemPostion();


private:
  Ui::WidgetLayoutMainWindow *ui;

  QGraphicsScene *scene;
  QGraphicsView *view;
  PidItem *pid;
  SumItem *sumItem;

  QGraphicsProxyWidget *sumWidget;
};

#endif // WIDGETLAYOUTMAINWINDOW_H
