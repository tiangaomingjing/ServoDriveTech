#include "cpumainwindow.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QThread::currentThread()->setPriority(QThread::LowestPriority);

  CpuMainWindow w;
  w.show();

  return a.exec();
}
