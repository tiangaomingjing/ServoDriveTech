#ifndef ANCHORMAINWINDOW_H
#define ANCHORMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AnchorMainWindow;
}

class AnchorMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AnchorMainWindow(QWidget *parent = 0);
  ~AnchorMainWindow();

private:
  Ui::AnchorMainWindow *ui;
};

#endif // ANCHORMAINWINDOW_H
