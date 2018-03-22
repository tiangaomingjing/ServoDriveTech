#include "comparisondialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComparisonDialog w;
    w.show();

    return a.exec();
}
