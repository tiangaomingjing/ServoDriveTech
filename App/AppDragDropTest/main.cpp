#include "dragdropmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DragDropMainWindow w;
  w.show();

  return a.exec();
}
