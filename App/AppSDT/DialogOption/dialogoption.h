#ifndef DIALOGOPTION_H
#define DIALOGOPTION_H

#include <QDialog>

namespace Ui {
class DialogOption;
}
class OptContainer;
class DialogOption : public QDialog
{
  Q_OBJECT

public:
  explicit DialogOption(QWidget *parent = 0);
  ~DialogOption();
private slots:
  void onListWidgetRowChanged(int index);
  void on_btn_apply_clicked();

  void on_btn_ok_clicked();

  void on_btn_cancel_clicked();

private:
  void closeEvent(QCloseEvent *e) override;

private:
  Ui::DialogOption *ui;
  OptContainer *m_optContainer;

};

#endif // DIALOGOPTION_H
