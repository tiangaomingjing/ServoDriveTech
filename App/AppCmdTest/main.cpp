#include "cmdmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CmdMainWindow w;
  w.show();

  return a.exec();
}
