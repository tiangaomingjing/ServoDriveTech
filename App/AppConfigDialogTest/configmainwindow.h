#ifndef CONFIGMAINWINDOW_H
#define CONFIGMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ConfigMainWindow;
}

class ConfigMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit ConfigMainWindow(QWidget *parent = 0);
  ~ConfigMainWindow();

private slots:
  void on_actionConfigTest_triggered();

private:
  Ui::ConfigMainWindow *ui;
};

#endif // CONFIGMAINWINDOW_H
