#include "customplotmainwindow.h"
#include "ui_customplotmainwindow.h"

CustomPlotMainWindow::CustomPlotMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CustomPlotMainWindow)
{
  ui->setupUi(this);
}

CustomPlotMainWindow::~CustomPlotMainWindow()
{
  delete ui;
}
