#include "appmainwindowtest.h"
#include <QApplication>
#include "UiFactory/registerfunction.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  RegisterFunction::registerUiClass();
  AppMainWindowTest w;
  w.show();

  return a.exec();
}
