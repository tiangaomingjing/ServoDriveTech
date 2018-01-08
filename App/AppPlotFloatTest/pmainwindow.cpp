#include "pmainwindow.h"
#include "ui_pmainwindow.h"

PMainWindow::PMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PMainWindow)
{
  ui->setupUi(this);
  QWidget*w=takeCentralWidget();
  delete w;
}

PMainWindow::~PMainWindow()
{
  delete ui;
}
