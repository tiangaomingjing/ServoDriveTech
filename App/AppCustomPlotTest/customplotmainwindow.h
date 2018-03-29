#ifndef CUSTOMPLOTMAINWINDOW_H
#define CUSTOMPLOTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CustomPlotMainWindow;
}

class CustomPlotMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit CustomPlotMainWindow(QWidget *parent = 0);
  ~CustomPlotMainWindow();

private:
  Ui::CustomPlotMainWindow *ui;
};

#endif // CUSTOMPLOTMAINWINDOW_H
