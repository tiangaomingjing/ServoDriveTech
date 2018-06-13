#include "nodeeditmainwindow.h"
#include "ui_nodeeditmainwindow.h"

#include <QGraphicsScene>

NodeEditMainWindow::NodeEditMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::NodeEditMainWindow)
{
  ui->setupUi(this);
  m_scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(m_scene);
}

NodeEditMainWindow::~NodeEditMainWindow()
{
  delete ui;
}
