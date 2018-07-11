#ifndef DRAGDROPMAINWINDOW_H
#define DRAGDROPMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class DragDropMainWindow;
}
class QHBoxLayout;

class DragDropMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit DragDropMainWindow(QWidget *parent = 0);
  ~DragDropMainWindow();

//protected:
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);

private:
  Ui::DragDropMainWindow *ui; 
};

#endif // DRAGDROPMAINWINDOW_H
