#include "animationmainwindow.h"
#include "ui_animationmainwindow.h"

#include <QPushButton>
#include <QLabel>

AnimationMainWindow::AnimationMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::AnimationMainWindow)
{
  ui->setupUi(this);
//  QPushButton *btn1=new QPushButton(this);
//  btn1->setGeometry(QRect(this->width()/2,this->height()/2,50,30));
//  QWidget *w=new QWidget(this);
//  w->setStyleSheet("background-color:black;");
//  w->setGeometry(QRect(10,10,this->width(),this->height()));
  label=new QLabel("test aaaaaaaaaaaaaaa");

}

AnimationMainWindow::~AnimationMainWindow()
{
  delete ui;
}

void AnimationMainWindow::on_actionShowWidget_triggered()
{
    ui->vLayout->addWidget(label);
    label->setVisible(true);
}

void AnimationMainWindow::on_actionHideWidget_triggered()
{
    ui->vLayout->removeWidget(label);
    label->setVisible(false);
}
