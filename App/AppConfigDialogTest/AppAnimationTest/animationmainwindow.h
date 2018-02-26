#ifndef ANIMATIONMAINWINDOW_H
#define ANIMATIONMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AnimationMainWindow;
}

class AnimationMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AnimationMainWindow(QWidget *parent = 0);
  ~AnimationMainWindow();

private:
  Ui::AnimationMainWindow *ui;
};

#endif // ANIMATIONMAINWINDOW_H
