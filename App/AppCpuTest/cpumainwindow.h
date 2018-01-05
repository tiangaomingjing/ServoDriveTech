#ifndef CPUMAINWINDOW_H
#define CPUMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CpuMainWindow;
}
class ISysInfo;
class CpuMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit CpuMainWindow(QWidget *parent = 0);
  ~CpuMainWindow();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_sleep_clicked();

  void on_pushButton_sleep_wait_clicked();

private:
  void cpuTest();

private:
  Ui::CpuMainWindow *ui;

  ISysInfo* m_sysInfo;
};

#endif // CPUMAINWINDOW_H
