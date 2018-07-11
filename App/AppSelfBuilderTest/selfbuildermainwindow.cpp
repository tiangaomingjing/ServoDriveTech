﻿#include "selfbuildermainwindow.h"
#include "ui_selfbuildermainwindow.h"
#include "selfbuilder.h"
#include "gtutils.h"
#include "rnnet.h"
#include <QDebug>

SelfBuilderMainWindow::SelfBuilderMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelfBuilderMainWindow)
{
    ui->setupUi(this);
//    QString path = GTUtils::commonPath();
//    qDebug()<<path;
//    BuilderParameters *para = new BuilderParameters(33333, 55555, "V131");
    BuilderParameters para(21000541, 21000543, "V130");
    ComDriver::ICom *tempCom = new ComDriver::RnNet();
    int ret = tempCom->open(0, 0);
    qDebug()<<"ret = "<<ret;
    SelfBuilder *builder = new SelfBuilder(tempCom);
    SelfBuilder::RtnSelf rtn =  builder->buildFromEprom(0, 0, &para);
    qDebug()<<"rtn = "<<rtn;
}

SelfBuilderMainWindow::~SelfBuilderMainWindow()
{
    delete ui;
}
