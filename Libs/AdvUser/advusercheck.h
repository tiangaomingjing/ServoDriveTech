#ifndef ADVUSERCHECK_H
#define ADVUSERCHECK_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include "iadvuser.h"


namespace Ui {
class AdvUserCheck;
}

class AdvUserCheckPrivate;

class ADVUSERSHARED_EXPORT AdvUserCheck : public IAdvUser
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AdvUserCheck)

public:
    explicit AdvUserCheck(const QString &advUserName, QWidget *parent = 0);
    ~AdvUserCheck();

    void uiInit() Q_DECL_OVERRIDE;
    bool isChecked();
    QString nickName()Q_DECL_OVERRIDE;
protected:
    bool advUserActive() Q_DECL_OVERRIDE;
    bool readAdv() Q_DECL_OVERRIDE;
    bool writeAdv() Q_DECL_OVERRIDE;
    void respondErrorExecute() Q_DECL_OVERRIDE;
signals:
    void checkChanged(bool isChecked);
private slots:
    void onActionLineChanged();
    void onActionBtnChecked();

private:
    Ui::AdvUserCheck *ui;
};

#endif // ADVUSERCHECK_H
