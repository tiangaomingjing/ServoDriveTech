#include "animationmainwindow.h"
#include "ui_animationmainwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QDebug>

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

  ui->comboBox->addItem("4M",0);
  ui->comboBox->addItem("2.5M",1);

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

void AnimationMainWindow::on_pushButton_clicked()
{
    qDebug()<<"combobox data:"<<ui->comboBox->currentData().toUInt();
}
