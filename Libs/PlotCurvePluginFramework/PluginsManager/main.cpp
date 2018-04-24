#include <QApplication>
#include "pluginsmanager.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  PluginsManager manager;
  manager.loadPlugins();


  return a.exec();
}

