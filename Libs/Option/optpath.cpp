#include "optpath.h"
#include "ui_optpath.h"

OptPath::OptPath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptPath)
{
    ui->setupUi(this);
}

OptPath::~OptPath()
{
    delete ui;
}
