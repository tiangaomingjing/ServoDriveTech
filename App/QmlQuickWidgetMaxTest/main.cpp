#include "qwmaxmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QwMaxMainWindow w;
  w.show();

  return a.exec();
}
