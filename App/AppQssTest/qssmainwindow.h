#ifndef QSSMAINWINDOW_H
#define QSSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QssMainWindow;
}

class QssMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit QssMainWindow(QWidget *parent = 0);
  ~QssMainWindow();

private slots:
  void on_actionQss1_triggered();

  void on_actionQss2_triggered();

  void on_actionQ3_triggered();

  void on_pushButton_fontsize_clicked();

private:
  Ui::QssMainWindow *ui;
};

#endif // QSSMAINWINDOW_H
