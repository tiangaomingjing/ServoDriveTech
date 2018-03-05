#include "anchormainwindow.h"
#include "ui_anchormainwindow.h"

AnchorMainWindow::AnchorMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AnchorMainWindow)
{
  ui->setupUi(this);
}

AnchorMainWindow::~AnchorMainWindow()
{
  delete ui;
}
