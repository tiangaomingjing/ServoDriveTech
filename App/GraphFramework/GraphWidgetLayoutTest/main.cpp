#include "widgetlayoutmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  WidgetLayoutMainWindow w;
  w.show();

  return a.exec();
}
