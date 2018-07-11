#include "pluginframeworkmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PluginFrameworkMainWindow w;
  w.show();

  return a.exec();
}
