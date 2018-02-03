#ifndef USERCHECKWIDGETPRIVATE_H
#define USERCHECKWIDGETPRIVATE_H

#include <QWidget>

namespace Ui {
class UserCheckWidgetPrivate;
}

class UserCheckWidgetPrivate : public QWidget
{
    Q_OBJECT

public:
    explicit UserCheckWidgetPrivate(QWidget *parent = 0);
    ~UserCheckWidgetPrivate();
    void setCheck(bool isChecked);
    bool isChecked();
    QString getPsw();
    void pswClear();
signals:
    void stateChanged();

private:
    Ui::UserCheckWidgetPrivate *ui;
private slots:
    void onStateChanged();
};

#endif // USERCHECKWIDGETPRIVATE_H
