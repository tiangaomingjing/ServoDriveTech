#ifndef DIALMAINWINDOW_H
#define DIALMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class DialMainWindow;
}
class QwtDial;
class QTimer;
class DialMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit DialMainWindow(QWidget *parent = 0);
  ~DialMainWindow();

private slots:
  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void onTimeOut();
  void on_pushButton_showENC_clicked();

private:
  void initDial(QwtDial *dial);

private:
  Ui::DialMainWindow *ui;
  QTimer *m_timerTest;
};

#endif // DIALMAINWINDOW_H
