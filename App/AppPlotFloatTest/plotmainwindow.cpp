#include "plotmainwindow.h"
#include "ui_plotmainwindow.h"
#include "pmainwindow.h"
#include <QLabel>

PlotMainWindow::PlotMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PlotMainWindow)
{
  ui->setupUi(this);
  PMainWindow *w=new PMainWindow;
  ui->verticalLayout_2->addWidget(w);

  mw=new QWidget;
  QVBoxLayout *layout=new QVBoxLayout(mw);
  QLabel *label=new QLabel("my test",mw);
  layout->addWidget(label);
  mw->setLayout(layout);
//  ui->verticalLayout_2->addWidget(mw);

}

PlotMainWindow::~PlotMainWindow()
{
  delete ui;
}

void PlotMainWindow::on_actionFloat_triggered()
{
//    ui->label->setParent(0);
//    ui->label->showMaximized();
  ui->verticalLayout_2->removeWidget(mw);
  mw->setParent(0);
  mw->show();
}

void PlotMainWindow::on_actionInFloat_triggered()
{
//    ui->label->setParent(this);
//    ui->verticalLayout_2->addWidget(ui->label);
  ui->verticalLayout_2->addWidget(mw);
  mw->setVisible(true);

}
