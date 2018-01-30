#include "graphmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  GraphMainWindow w;
  w.show();

  return a.exec();
}
