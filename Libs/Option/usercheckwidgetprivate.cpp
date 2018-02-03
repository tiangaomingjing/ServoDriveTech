#include "usercheckwidgetprivate.h"
#include "ui_usercheckwidgetprivate.h"
#include <QDebug>

UserCheckWidgetPrivate::UserCheckWidgetPrivate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserCheckWidgetPrivate)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(onStateChanged()));
    //connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(onStateChanged()));
}

UserCheckWidgetPrivate::~UserCheckWidgetPrivate()
{
    delete ui;
}

void UserCheckWidgetPrivate::setCheck(bool isChecked) {
    ui->checkBox->setChecked(isChecked);
}

bool UserCheckWidgetPrivate::isChecked() {
    return ui->checkBox->isChecked();
}

QString UserCheckWidgetPrivate::getPsw() {
    return ui->lineEdit->text();
}

void UserCheckWidgetPrivate::onStateChanged() {
    qDebug()<<"ss";
    emit stateChanged();
}

void UserCheckWidgetPrivate::pswClear() {
    ui->lineEdit->clear();
}
