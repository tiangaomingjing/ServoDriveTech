#include "plotmainwindow.h"
#include "ui_plotmainwindow.h"
#include "pmainwindow.h"
#include "floatwidget.h"

#include <QLabel>

PlotMainWindow::PlotMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PlotMainWindow)
{
  ui->setupUi(this);
//  PMainWindow *w=new PMainWindow;
//  ui->verticalLayout_2->addWidget(w);


//  ui->verticalLayout_2->addWidget(mw);
  m_floatWidget=new FloatWidget;
  accept(m_floatWidget);

}

PlotMainWindow::~PlotMainWindow()
{
  delete ui;
}

void PlotMainWindow::accept(QWidget *w)
{
  m_floatWidget=dynamic_cast<FloatWidget *>(w);
  ui->verticalLayout_2->addWidget(m_floatWidget);
  connect(m_floatWidget,SIGNAL(btnIn(bool)),this,SLOT(onBtnInClicked(bool)));
}

void PlotMainWindow::on_actionFloat_triggered()
{
  m_floatWidget->show();
}

void PlotMainWindow::on_actionInFloat_triggered()
{


}

void PlotMainWindow::onBtnInClicked(bool in)
{
  if(in)
  {
    ui->verticalLayout_2->addWidget(m_floatWidget);
    m_floatWidget->setVisible(true);
  }
  else
  {
    ui->verticalLayout_2->removeWidget(m_floatWidget);
    m_floatWidget->setParent(0);
    m_floatWidget->showMaximized();
  }
}
