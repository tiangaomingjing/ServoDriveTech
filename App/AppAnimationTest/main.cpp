#include "animationmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AnimationMainWindow w;
  w.show();

  return a.exec();
}
