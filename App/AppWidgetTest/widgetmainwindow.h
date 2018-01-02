#ifndef WIDGETMAINWINDOW_H
#define WIDGETMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class WidgetMainWindow;
}

class WidgetMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit WidgetMainWindow(QWidget *parent = 0);
  ~WidgetMainWindow();

private:
  Ui::WidgetMainWindow *ui;
};

#endif // WIDGETMAINWINDOW_H
