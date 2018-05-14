#ifndef DIALOGADVUSR_H
#define DIALOGADVUSR_H

#include <QDialog>

namespace Ui {
class DialogAdvUsr;
}

class AdvUserContainer;

class DialogAdvUsr : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAdvUsr(QWidget *parent = 0);
    ~DialogAdvUsr();

private:
    Ui::DialogAdvUsr *ui;
    AdvUserContainer *m_advContainer;
private:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void onListWidgetRowChanged(int row);
    void onOkButtonClicked();
    void onCancelButtonClicked();
    void onApplyButtonClicked();
};

#endif // DIALOGADVUSR_H
