#include "optionmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  OptionMainWindow w;
  w.show();

  return a.exec();
}
