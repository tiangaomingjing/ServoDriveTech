#ifndef QSSMAINWINDOW_H
#define QSSMAINWINDOW_H

#include <QMainWindow>
#include "stylewidget.h"

namespace Ui {
class QssMainWindow;
}
class QProcess;
class ISysInfo;
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

  void on_pushButton_clicked();

  void on_actionSpinDefault_triggered();

  void on_actionSpinReady_triggered();

  void on_actionSpinError_triggered();

  void on_actionSpinEditting_triggered();

  void on_actionStyleTest1_triggered();

  void on_actionStyleTest2_triggered();

private:
  void testCupInfo();

private:
  Ui::QssMainWindow *ui;
  QProcess *p;
  ISysInfo *m_sysInfo;
  StyleWidget style;
};

#endif // QSSMAINWINDOW_H
