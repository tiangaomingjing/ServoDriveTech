#ifndef ALARMLEDMAINWINDOW_H
#define ALARMLEDMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AlarmLedMainWindow;
}
class LedAlarm;
class AlarmLedMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AlarmLedMainWindow(QWidget *parent = 0);
  ~AlarmLedMainWindow();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::AlarmLedMainWindow *ui;
  LedAlarm *led;
};

#endif // ALARMLEDMAINWINDOW_H
