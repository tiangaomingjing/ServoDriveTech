#ifndef PLOTMAINWINDOW_H
#define PLOTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlotMainWindow;
}
class FloatWidget;

class PlotMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit PlotMainWindow(QWidget *parent = 0);
  ~PlotMainWindow();

  void accept(QWidget *w);

private slots:
  void on_actionFloat_triggered();

  void on_actionInFloat_triggered();

  void onBtnInClicked(bool in);

private:
  Ui::PlotMainWindow *ui;
  FloatWidget *m_floatWidget;
};

#endif // PLOTMAINWINDOW_H
