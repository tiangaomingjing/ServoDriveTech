#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>

namespace Ui {
class InfoDialog;
}

class SevDevice;

class InfoDialog : public QDialog
{
    Q_OBJECT

    typedef enum {
        COL_NAME = 0,
        COL_C = 1,
        COL_V = 2,
        COL_F = 3,
        COL_P = 4,
        COL_MATCH = 5
    }ColDb;

public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();
    void uiInit(const QList<SevDevice*> &devList);
private:

private:
    Ui::InfoDialog *ui;
    QList<SevDevice*> m_devList;
};

#endif // INFODIALOG_H
