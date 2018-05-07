#ifndef PLUGINMAINWINDOW_H
#define PLUGINMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PluginMainWindow;
}

class PluginMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit PluginMainWindow(QWidget *parent = 0);
  ~PluginMainWindow();

private:
  Ui::PluginMainWindow *ui;
};

#endif // PLUGINMAINWINDOW_H
