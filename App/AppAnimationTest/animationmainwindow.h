#ifndef ANIMATIONMAINWINDOW_H
#define ANIMATIONMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AnimationMainWindow;
}
class QLabel;
class AnimationMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AnimationMainWindow(QWidget *parent = 0);
  ~AnimationMainWindow();

private slots:
  void on_actionShowWidget_triggered();

  void on_actionHideWidget_triggered();

  void on_pushButton_clicked();

private:
  Ui::AnimationMainWindow *ui;
  QLabel *label;
};

#endif // ANIMATIONMAINWINDOW_H
