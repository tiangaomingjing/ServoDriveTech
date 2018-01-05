#ifndef QSSMAINWINDOW_H
#define QSSMAINWINDOW_H

#include <QMainWindow>

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

private:
  void testCupInfo();

private:
  Ui::QssMainWindow *ui;
  QProcess *p;
  ISysInfo *m_sysInfo;
};

#endif // QSSMAINWINDOW_H
