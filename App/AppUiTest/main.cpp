#include "uimainwindow.h"
#include <QApplication>
#include <QTranslator>

#include "gtutils.h"
#include "UiFactory/registerfunction.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  RegisterFunction::registerUiClass();
  QString langPath= GTUtils::languagePath();
  QTranslator trans;
  trans.load("en_main.qm",langPath);
  a.installTranslator(&trans);

  UiMainWindow w;
  w.showMaximized();
  w.init();

  return a.exec();
}
