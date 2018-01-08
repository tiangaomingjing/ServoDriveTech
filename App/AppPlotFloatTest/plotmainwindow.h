#ifndef PLOTMAINWINDOW_H
#define PLOTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlotMainWindow;
}

class PlotMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit PlotMainWindow(QWidget *parent = 0);
  ~PlotMainWindow();

private slots:
  void on_actionFloat_triggered();

  void on_actionInFloat_triggered();

private:
  Ui::PlotMainWindow *ui;
  QWidget *mw;
};

#endif // PLOTMAINWINDOW_H
