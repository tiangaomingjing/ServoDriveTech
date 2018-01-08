#ifndef PMAINWINDOW_H
#define PMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PMainWindow;
}

class PMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit PMainWindow(QWidget *parent = 0);
  ~PMainWindow();

private:
  Ui::PMainWindow *ui;
};

#endif // PMAINWINDOW_H
