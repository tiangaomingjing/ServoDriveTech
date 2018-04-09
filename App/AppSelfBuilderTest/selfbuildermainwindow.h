#ifndef SELFBUILDERMAINWINDOW_H
#define SELFBUILDERMAINWINDOW_H

#include <QMainWindow>
#include "gtutils_global.h"

namespace ComDriver {
  class ICom;
}

namespace Ui {
class SelfBuilderMainWindow;
}

class SelfBuilderMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelfBuilderMainWindow(QWidget *parent = 0);
    ~SelfBuilderMainWindow();

private:
    Ui::SelfBuilderMainWindow *ui;
};

#endif // SELFBUILDERMAINWINDOW_H
