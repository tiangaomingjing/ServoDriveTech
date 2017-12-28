#include "optionmainwindow.h"
#include "ui_optionmainwindow.h"

#include "dialogoption.h"
#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"

#include <QDebug>

OptionMainWindow::OptionMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::OptionMainWindow)
{
  ui->setupUi(this);

}

OptionMainWindow::~OptionMainWindow()
{
  delete ui;
}

void OptionMainWindow::on_actionOption_triggered()
{
    DialogOption dialogOpt;
    OptContainer *optc=OptContainer::instance();
    foreach (IOpt *opt, optc->optItems())
    {
      opt->uiInit();
    }
    dialogOpt.exec();
}

void OptionMainWindow::closeEvent(QCloseEvent *e)
{
  OptContainer *optc=OptContainer::instance();
  optc->saveOpt();
  QMainWindow::closeEvent(e);
}
