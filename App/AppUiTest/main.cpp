#include "uimainwindow.h"
#include <QApplication>
#include "UiFactory/registerfunction.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  RegisterFunction::registerUiClass();

  UiMainWindow w;
  w.showMaximized();
  w.init();

  return a.exec();
}
