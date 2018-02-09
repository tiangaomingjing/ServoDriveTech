#ifndef CMDMAINWINDOW_H
#define CMDMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CmdMainWindow;
}

class CmdMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit CmdMainWindow(QWidget *parent = 0);
  ~CmdMainWindow();

private slots:
  void on_pushButton_fillmaps_clicked();

private:
  Ui::CmdMainWindow *ui;
};

#endif // CMDMAINWINDOW_H
