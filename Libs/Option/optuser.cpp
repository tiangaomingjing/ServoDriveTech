#include "optuser.h"
#include "iopt_p.h"
#include "ui_optuser.h"
#include "gtutils.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#define ADMINPW_FILE "adminpw/admin.psw"

class OptUserPrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptUser)
public:
  OptUserPrivate();
  ~OptUserPrivate();
  bool m_isAdmin;
  QString m_pw;
  QString m_errMsg;
};
OptUserPrivate::OptUserPrivate():m_isAdmin(false),m_pw("")
{

}
OptUserPrivate::~OptUserPrivate()
{

}

OptUser::OptUser(const QString &optName, QWidget *parent) : IOpt(optName,*new OptUserPrivate,parent),
  ui(new Ui::OptUser)
{
  //Q_D(OptUser);
  ui->setupUi(this);
  ui->lineEdit->setEchoMode(QLineEdit::Password);

  readOpt();
  uiInit();
  connect(ui->btn_Admin, SIGNAL(clicked()), this, SLOT(onActionBtnChecked()));
  connect(ui->btn_General, SIGNAL(clicked()), this, SLOT(onActionBtnChecked()));
  connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(onActionLineChange()));
}
OptUser::~OptUser()
{
  //Q_D(OptUser);
  delete ui;
}
void OptUser::uiInit()
{
    Q_D(OptUser);
    qDebug()<<"user ui Init";
    setModify(false);
//    d->m_isAdmin=data("usr","admin",false).toBool();
//    d->m_isChecked = data("usr", "check", true).toBool();

    ui->pswWidget->setVisible(d->m_isAdmin);
    ui->btn_Admin->setChecked(d->m_isAdmin);
    ui->btn_General->setChecked(!d->m_isAdmin);
}

bool OptUser::optActive()
{
  Q_D(OptUser);
    d->m_isAdmin = ui->btn_Admin->isChecked();
  qDebug()<<"opt user execute active ";
    if (d->m_isAdmin) {
        QString password = ui->lineEdit->text();
        if (password.compare(d->m_pw) == 0) {
            ui->lineEdit->setReadOnly(true);
            emit usrChange(d->m_isAdmin);
        } else {
            d->m_errMsg = tr("Wrong Password!");
            //QMessageBox::warning(this, tr("Warning"), tr("Wrong Password!"), QMessageBox::Ok);
            return false;
        }
    } else {
        emit usrChange(d->m_isAdmin);
    }
  return true;
}
bool OptUser::readOpt()
{
  Q_D(OptUser);
  d->m_isAdmin=data("usr","admin",false).toBool();
  d->m_pw=data("usr","psw","googol123").toString();
  qDebug()<<"optusr read opt";

//  QString pwFile=GTUtils::customPath()+ADMINPW_FILE;
//  QFile file;
//  file.setFileName(pwFile);
//  if(file.open(QIODevice::ReadOnly))
//  {
//    QTextStream in(&file);
//    d->m_pw=in.readAll();
//    file.close();
//  }
//  else
//  {
//    qDebug()<<"can not open file:"<<pwFile;
//    d->m_pw="googol123";
//  }

  return true;
}
bool OptUser::writeOpt()
{
    Q_D(OptUser);
//  saveData("usr","admin",d->m_isAdmin);
//  saveData("usr","psw",d->m_pw);
  return true;
}

void OptUser::respondErrorExecute()
{
    Q_D(OptUser);
    QMessageBox::warning(this, tr("Warning"), d->m_errMsg, QMessageBox::Ok);
}

bool OptUser::isAdmin() const
{
  Q_D(const OptUser);
    return d->m_isAdmin;
}

QString OptUser::nickName()
{
    return tr("User");
}

void OptUser::onActionBtnChecked() {
    //Q_D(OptUser);
    setModify(true);
    if (ui->btn_Admin->isChecked()) {
        ui->pswWidget->setVisible(true);
    } else {
        ui->lineEdit->clear();
        ui->lineEdit->setReadOnly(false);
        ui->pswWidget->setVisible(false);
    }
}

void OptUser::onActionLineChange() {
    setModify(true);
}
