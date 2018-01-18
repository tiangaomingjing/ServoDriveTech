#ifndef QWMAXMAINWINDOW_H
#define QWMAXMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QwMaxMainWindow;
}

class QwMaxMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QwMaxMainWindow(QWidget *parent = 0);
  ~QwMaxMainWindow();

private slots:
  void on_actionQuickwidgetTest_triggered();

  void on_actionSceneViewTest_triggered();

private:
  Ui::QwMaxMainWindow *ui;
};

#endif // QWMAXMAINWINDOW_H
