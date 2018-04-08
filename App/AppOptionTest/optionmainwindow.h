#ifndef OPTIONMAINWINDOW_H
#define OPTIONMAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class OptionMainWindow;
}
class FormLangTest1;
class FormLangTest2;

class OptionMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit OptionMainWindow(QWidget *parent = 0);
  ~OptionMainWindow();

private slots:
  void on_actionOption_triggered();

  void onToolBtnClicked();
  void onToolBtnActionClicked();
  void on_pushButton_clicked();

  void on_actionTransTest1_triggered();

  void on_actionTransTest2_triggered();

private:
  void closeEvent(QCloseEvent *e);
  void TEST_getAllFileInOneFolder();
  void setStyleSheetFromFile();

private:
  Ui::OptionMainWindow *ui;
  FormLangTest1 *form1;
  FormLangTest2 *form2;
};

#endif // OPTIONMAINWINDOW_H
