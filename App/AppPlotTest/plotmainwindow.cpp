#include "plotmainwindow.h"
#include "ui_plotmainwindow.h"
#include "modectlpanel.h"

#include <QVBoxLayout>
#include <QDebug>

PlotMainWindow::PlotMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PlotMainWindow)
{
  ui->setupUi(this);
  QVBoxLayout *layout=new QVBoxLayout;
  ui->centralWidget->setLayout(layout);
  ModeCtlPanel *panel=new ModeCtlPanel(6,this);
  layout->addWidget(panel);
}

PlotMainWindow::~PlotMainWindow()
{
  delete ui;
}

void PlotMainWindow::onAxisModeClearOthers(quint16 axis)
{

}

void PlotMainWindow::onAxisModeChanged(quint16 axis,int mode)
{
  qDebug()<<"axis"<<axis<<"mode"<<mode;
}
