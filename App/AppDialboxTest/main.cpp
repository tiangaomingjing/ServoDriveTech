#include "dialmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DialMainWindow w;
  w.show();

  return a.exec();
}
