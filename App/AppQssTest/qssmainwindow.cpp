#include "qssmainwindow.h"
#include "ui_qssmainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

QssMainWindow::QssMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::QssMainWindow)
{
  ui->setupUi(this);
}

QssMainWindow::~QssMainWindow()
{
  delete ui;
}

void QssMainWindow::on_actionQss1_triggered()
{
  QString filename=qApp->applicationDirPath()+"/qss/qss1.css";
  qDebug()<<filename;
  QFile file(filename);
  file.open(QFile::ReadOnly);
  QTextStream in(&file);

  QString qss = in.readAll();
  qApp->setStyleSheet(qss);

}

void QssMainWindow::on_actionQss2_triggered()
{
  QString filename=qApp->applicationDirPath()+"/qss/qss2.css";
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
