#include "eprommanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EpromManager w;
    w.show();

    return a.exec();
}
