#include "animationmainwindow.h"
#include "ui_animationmainwindow.h"

#include <QPushButton>

AnimationMainWindow::AnimationMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AnimationMainWindow)
{
  ui->setupUi(this);
  QPushButton *btn1=new QPushButton(this);
  btn1->setGeometry(QRect(this->width()/2,this->height()/2,50,30));
  QWidget *w=new QWidget(this);
  w->setStyleSheet("background-color:black;");
  w->setGeometry(QRect(10,10,this->width(),this->height()));

}

AnimationMainWindow::~AnimationMainWindow()
{
  delete ui;
}
