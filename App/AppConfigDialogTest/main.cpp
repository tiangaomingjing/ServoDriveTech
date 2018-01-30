#include "configmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ConfigMainWindow w;
  w.show();

  return a.exec();
}
