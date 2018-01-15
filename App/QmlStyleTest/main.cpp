#include "qmlstylewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QmlStyleWindow w;
  w.show();

  return a.exec();
}
