#include "tabmotion.h"
#include "ui_tabmotion.h"

TabMotion::TabMotion(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TabMotion)
{
  ui->setupUi(this);
}

TabMotion::~TabMotion()
{
  delete ui;
}
