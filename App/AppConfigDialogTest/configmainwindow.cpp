#include "configmainwindow.h"
#include "ui_configmainwindow.h"
#include "configdialog.h"
#include "deviceconfig.h"

ConfigMainWindow::ConfigMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ConfigMainWindow)
{
  ui->setupUi(this);
}

ConfigMainWindow::~ConfigMainWindow()
{
  delete ui;
}

void ConfigMainWindow::on_actionConfigTest_triggered()
{
  QList<DeviceConfig *>list;
  ConfigDialog dia(&list,0);
  dia.exec();
}
