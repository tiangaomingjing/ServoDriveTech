#include "alarmledmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AlarmLedMainWindow w;
  w.show();

  return a.exec();
}
