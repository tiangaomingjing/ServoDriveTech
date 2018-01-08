#include "plotmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PlotMainWindow w;
  w.show();

  return a.exec();
}
