#include "comparisondialog.h"
#include "updatedtreewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComparisonDialog w;
    w.show();
//    Form f;
//    f.show();
//    UpdatedTreeWidget t;
//    t.show();


    return a.exec();
}
