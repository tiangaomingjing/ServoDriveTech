#ifndef OPTPATH_H
#define OPTPATH_H

#include <QWidget>

namespace Ui {
class OptPath;
}

class OptPath : public QWidget
{
    Q_OBJECT

public:
    explicit OptPath(QWidget *parent = 0);
    ~OptPath();

private:
    Ui::OptPath *ui;
};

#endif // OPTPATH_H
