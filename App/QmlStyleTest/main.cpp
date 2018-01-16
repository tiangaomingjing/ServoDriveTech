#include "qmlstylewindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QString lang="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/App/QmlStyleTest/qlangtest.qm";
  QTranslator trans;
  trans.load(lang);
  a.installTranslator(&trans);

  QmlStyleWindow w;
  w.show();

  return a.exec();
}
