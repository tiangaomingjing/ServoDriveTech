#ifndef CMDMAINWINDOW_H
#define CMDMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CmdMainWindow;
}
class GeneralCmd;
class CmdMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit CmdMainWindow(QWidget *parent = 0);
  ~CmdMainWindow();

private slots:
  void on_pushButton_fillmaps_clicked();

  void on_pushButton_open_clicked();

  void on_pushButton_16Read_clicked();

  void on_pushButton_32Read_clicked();

  void on_pushButton_16Write_clicked();

  void on_pushButton_32Write_clicked();

private:
  Ui::CmdMainWindow *ui;
  GeneralCmd *m_gencmd;
};

#endif // CMDMAINWINDOW_H
