#include "appxmlrwtest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppXmlRWTest w;
    w.show();

    return a.exec();
}
