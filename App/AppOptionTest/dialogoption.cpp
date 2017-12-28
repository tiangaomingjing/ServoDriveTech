#include "dialogoption.h"
#include "ui_dialogoption.h"

#include "optautoload.h"
#include "iopt.h"
#include "optcontainer.h"
#include "optface.h"
#include "optplot.h"
#include "optuser.h"

#include <QDebug>

DialogOption::DialogOption(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogOption)
{
  ui->setupUi(this);
  connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(onListWidgetRowChanged(int)));

  QWidget *w;
  while(ui->stackedWidget->count())
  {
    w=ui->stackedWidget->widget(0);
    delete w;
  }
  qDebug()<<"add opt widget";

  m_optContainer=OptContainer::instance();
  qDebug()<<"opt count "<<m_optContainer->optItems().count();
  QListWidgetItem *item;
  foreach (IOpt *iopt, m_optContainer->optItems()) {
    ui->stackedWidget->addWidget(iopt);
    item=new QListWidgetItem(iopt->name(),ui->listWidget);
//    item->setIcon();
    ui->listWidget->addItem(item);
    qDebug()<<"opt name :"<<iopt->name();
  }
  qDebug()<<"stacked widget count"<<ui->stackedWidget->count();
}

DialogOption::~DialogOption()
{
  delete ui;
  qDebug()<<"DialogOpt destruct-->";
}

void DialogOption::onListWidgetRowChanged(int index)
{
  ui->stackedWidget->setCurrentIndex(index);
}

void DialogOption::closeEvent(QCloseEvent *e)
{
  QWidget *w;
  qDebug()<<"close event :stackedwidget count"<<ui->stackedWidget->count();
  //为了避免其析构时，将stackedwidget上面的widget删除，全局都要使用
  while(ui->stackedWidget->count())
  {
    w=ui->stackedWidget->widget(0);
    w->setParent(0);
    qDebug()<<"reparent";
  }
//  m_optContainer->saveOpt();

  QDialog::closeEvent(e);
}

void DialogOption::on_btn_apply_clicked()
{
  qDebug()<<"apply clicked";
  QWidget *w=ui->stackedWidget->currentWidget();
  IOpt *opt=dynamic_cast<IOpt *>(w);
  opt->execute();
}

void DialogOption::on_btn_ok_clicked()
{
  qDebug()<<"ok clicked";
  OptContainer *optc=OptContainer::instance();
  bool ok=true;
  int errIndex;
  int i=0;
  foreach (IOpt *opt, optc->optItems())
  {
    ok=opt->execute();
    if(!ok)
      errIndex=i;
    i++;
  }
  if(!ok)
    ui->stackedWidget->setCurrentIndex(errIndex);
  else
    close();
}

void DialogOption::on_btn_cancel_clicked()
{
    close();
}
