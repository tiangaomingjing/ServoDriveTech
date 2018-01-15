#include "qmlstylewindow.h"
#include "ui_qmlstylewindow.h"

QmlStyleWindow::QmlStyleWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QmlStyleWindow)
{
  ui->setupUi(this);
}

QmlStyleWindow::~QmlStyleWindow()
{
  delete ui;
}
