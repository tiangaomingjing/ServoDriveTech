#include "pluginmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PluginMainWindow w;
  w.show();

  return a.exec();
}
