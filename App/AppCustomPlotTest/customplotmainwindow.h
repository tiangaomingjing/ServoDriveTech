#ifndef CUSTOMPLOTMAINWINDOW_H
#define CUSTOMPLOTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CustomPlotMainWindow;
}
class QCustomPlot;
class GtPlot;
class CustomPlotMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit CustomPlotMainWindow(QWidget *parent = 0);
  ~CustomPlotMainWindow();

private slots:
  void on_actionFix_triggered();

  void onPlotPosChanged(const QPointF &point);
  void onVtagPosChanged(qreal v1, qreal v2, qreal dv);
  void onHtagPosChanged(qreal v1,qreal v2,qreal dv);

  void on_actionHMea_triggered(bool checked);

  void on_actionVMea_triggered(bool checked);

private:
  void setupSimpleDemo(QCustomPlot *customPlot);

private:
  Ui::CustomPlotMainWindow *ui;
  GtPlot *plot;
};

#endif // CUSTOMPLOTMAINWINDOW_H
