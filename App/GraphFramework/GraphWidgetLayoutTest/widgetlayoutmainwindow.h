#ifndef WIDGETLAYOUTMAINWINDOW_H
#define WIDGETLAYOUTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class WidgetLayoutMainWindow;
}
class QGraphicsScene;
class QGraphicsView;
class PidItem;

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
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;


private:
  Ui::WidgetLayoutMainWindow *ui;

  QGraphicsScene *scene;
  QGraphicsView *view;
  PidItem *pid;
};

#endif // WIDGETLAYOUTMAINWINDOW_H
