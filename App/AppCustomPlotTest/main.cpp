#include "customplotmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CustomPlotMainWindow w;
  w.show();

  return a.exec();
}
