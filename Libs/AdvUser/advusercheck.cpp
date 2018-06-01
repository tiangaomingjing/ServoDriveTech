#include "advusercheck.h"
#include "ui_advusercheck.h"
#include "iadvuser_p.h"
#include "gtutils.h"

#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

#define ADMINPW_FILE "adminpw/admin.psw"

class AdvUserCheckPrivate : public IAdvUserPrivate {
    Q_DECLARE_PUBLIC(AdvUserCheck)
public:
    AdvUserCheckPrivate();
    ~AdvUserCheckPrivate();
    bool m_isChecked;
    QString m_pw;
    QString m_errMsg;
};

AdvUserCheckPrivate::AdvUserCheckPrivate():m_isChecked(false),m_pw("") {

}

AdvUserCheckPrivate::~AdvUserCheckPrivate() {

}

AdvUserCheck::AdvUserCheck(const QString &advUserName, QWidget *parent) :
    IAdvUser(advUserName, *new AdvUserCheckPrivate, parent),
    ui(new Ui::AdvUserCheck)
{
    ui->setupUi(this);
    ui->lineEdit_advPsw->setEchoMode(QLineEdit::Password);
    readAdv();
    uiInit();
    connect(ui->checkBox_advCheckData, SIGNAL(stateChanged(int)), this, SLOT(onActionBtnChecked()));
    connect(ui->lineEdit_advPsw, SIGNAL(textEdited(QString)), this, SLOT(onActionLineChanged()));
}

AdvUserCheck::~AdvUserCheck()
{
    delete ui;
}

void AdvUserCheck::uiInit()
{
    Q_D(AdvUserCheck);
    setModify(false);
    ui->checkBox_advCheckData->setChecked(d->m_isChecked);
}

bool AdvUserCheck::isChecked()
{
    Q_D(AdvUserCheck);
    return d->m_isChecked;
}

bool AdvUserCheck::advUserActive()
{
    Q_D(AdvUserCheck);
    d->m_isChecked = ui->checkBox_advCheckData->isChecked();
    QString psw = ui->lineEdit_advPsw->text();
    if (psw.compare(d->m_pw) == 0) {
        ui->lineEdit_advPsw->clear();
        emit checkChanged(d->m_isChecked);
    } else {
        d->m_errMsg = tr("Wrong Password!");
        return false;
    }
    return true;
}

bool AdvUserCheck::readAdv()
{
    Q_D(AdvUserCheck);
    d->m_isChecked = dataFromFile("advCheck", "isCheck", false).toBool();
    d->m_pw = dataFromFile("advCheck", "psw", "googol123").toString();
    return true;
}

bool AdvUserCheck::writeAdv()
{
    Q_D(AdvUserCheck);
//    saveDataToFile("advCheck", "isCheck", d->m_isChecked);
    return true;
}

void AdvUserCheck::respondErrorExecute()
{
    Q_D(AdvUserCheck);
    QMessageBox::warning(this, tr("Warning"), d->m_errMsg, QMessageBox::Ok);
}

void AdvUserCheck::onActionLineChanged()
{
    setModify(true);
}

void AdvUserCheck::onActionBtnChecked()
{
    setModify(true);
}
