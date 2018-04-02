#ifndef CUSTOMPLOTMAINWINDOW_H
#define CUSTOMPLOTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CustomPlotMainWindow;
}
class QCustomPlot;
class CustomPlotMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit CustomPlotMainWindow(QWidget *parent = 0);
  ~CustomPlotMainWindow();

protected:
  void keyPressEvent(QKeyEvent *event);

private slots:
  void on_actionFix_triggered();
  void onPlotMouseMoveEvent(QMouseEvent *event);
  void onPlotMousePressEvent(QMouseEvent *event);
  void onPlotMouseReleaseEvent(QMouseEvent *event);

  void onPlotPosChanged(const QPointF &point);
  void onVtagPosChanged(qreal data);
  void onHtagPosChanged(qreal data);

private:
  void setupSimpleDemo(QCustomPlot *customPlot);

private:
  Ui::CustomPlotMainWindow *ui;
};

#endif // CUSTOMPLOTMAINWINDOW_H
