#include "pluginmainwindow.h"
#include "ui_pluginmainwindow.h"

PluginMainWindow::PluginMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PluginMainWindow)
{
  ui->setupUi(this);
}

PluginMainWindow::~PluginMainWindow()
{
  delete ui;
}
