#include "qssmainwindow.h"
#include "ui_qssmainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDir>
#include "styleiconwidget.h"


QssMainWindow::QssMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QssMainWindow)
{
  ui->setupUi(this);
  QPushButton *button=new QPushButton(this);
  button->setText(tr("button new by code"));
  ui->verticalLayout->addWidget(button);

  //test StyleIconWidget
  QGridLayout *gridLayout=new QGridLayout();
  ui->verticalLayout->addLayout(gridLayout);
  QString fn="D:\\Smart\\ServoMaster\\git-project\\ServoDriveTech\\build-ServoDriveTech-Qt5_5_1Vs2013x86-Debug\\App\\AppQssTest\\qss\\icon";

  StyleIconWidget *s1=new StyleIconWidget(fn+"\\s1.png","blue",this);
  StyleIconWidget *s2=new StyleIconWidget(fn+"\\s2.png","gray",this);
  StyleIconWidget *s3=new StyleIconWidget(fn+"\\s3.png","red",this);
  StyleIconWidget *s4=new StyleIconWidget(fn+"\\s4.png","yellow",this);
  gridLayout->addWidget(s1,0,0);
  gridLayout->addWidget(s2,0,1);
  gridLayout->addWidget(s3,1,0);
  gridLayout->addWidget(s4,1,1);
}

QssMainWindow::~QssMainWindow()
{
  delete ui;
}

void QssMainWindow::on_actionQss1_triggered()
{

  QString filename=QApplication::applicationDirPath();
  QDir dir(filename);
  dir.cdUp();
  filename=dir.absolutePath()+"/qss/qss1.css";
  qDebug()<<filename;

  QFile file(filename);
  file.open(QFile::ReadOnly);
  QTextStream in(&file);

  QString qss = in.readAll();
  qApp->setStyleSheet(qss);

}

void QssMainWindow::on_actionQss2_triggered()
{
  QString filename=QApplication::applicationDirPath();
  QDir dir(filename);
  dir.cdUp();
  filename=dir.absolutePath()+"/qss/qss2.css";
  qDebug()<<filename;
  QFile file(filename);
  file.open(QFile::ReadOnly);
  QTextStream in(&file);

  QString qss = in.readAll();
  qApp->setStyleSheet(qss);
}

void QssMainWindow::on_actionQ3_triggered()
{
  QString qss="QPushButton{\
      border-style: none;\
      border: 0px;\
      color: #F0F0F0;\
      padding: 5px;\
      min-height: 20px;\
      border-radius:5px;\
      background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #4D4D4D, stop:1 #292929);\
    }";
qApp->setStyleSheet(qss);
}

void QssMainWindow::on_pushButton_fontsize_clicked()
{
  QFont font=qApp->font();
  font.setPixelSize(ui->spinBox->value());
  qApp->setFont(font);
  //还要再设置一下样式，才能更新
}
