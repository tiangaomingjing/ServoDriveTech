#include "qssmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QssMainWindow w;
  w.show();

  return a.exec();
}
