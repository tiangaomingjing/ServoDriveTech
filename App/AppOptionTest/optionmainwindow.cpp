﻿#include "optionmainwindow.h"
#include "ui_optionmainwindow.h"

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

  OptContainer *optc=OptContainer::instance(this);
  IOpt *opt=new OptFace("optface",0);
  optc->addOptItem(opt);
  opt=new OptUser("optuser",0);
  optc->addOptItem(opt);
  opt=new OptAutoLoad("optautoload",0);
  optc->addOptItem(opt);
  qDebug()<<".......................";
  opt=new OptPlot("optplot",0);
  optc->addOptItem(opt);
  qDebug()<<".......................2";
}

OptionMainWindow::~OptionMainWindow()
{
  delete ui;
}
