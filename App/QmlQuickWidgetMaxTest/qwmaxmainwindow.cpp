#include "qwmaxmainwindow.h"
#include "ui_qwmaxmainwindow.h"

#include <QtQml>
#include <QQuickWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

QwMaxMainWindow::QwMaxMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QwMaxMainWindow)
{
  ui->setupUi(this);

}

QwMaxMainWindow::~QwMaxMainWindow()
{
  delete ui;
}

void QwMaxMainWindow::on_actionQuickwidgetTest_triggered()
{
  for(int i=0;i<ui->spinBox->value();i++)
  {
    QQuickWidget *w=new QQuickWidget;
//    w->rootContext()->setContextProperty("mainwindows",this);
    ui->stackedWidget->addWidget(w);
  }
}

void QwMaxMainWindow::on_actionSceneViewTest_triggered()
{
  for(int i=0;i<ui->spinBox->value();i++)
  {
    QGraphicsScene *scene=new QGraphicsScene;
    QGraphicsView *view=new QGraphicsView(scene);
    ui->stackedWidget->addWidget(view);
    qDebug()<<"add view "<<i;
  }
}
