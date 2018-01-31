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
  Q_D(OptUser);
  ui->setupUi(this);
  readOpt();

  QString pwFile=GTUtils::customPath()+ADMINPW_FILE;
  QFile file;
  file.setFileName(pwFile);
  if(file.open(QIODevice::ReadOnly))
  {
    QTextStream in(&file);
    d->m_pw=in.readAll();
    file.close();
  }
  else
  {
    qDebug()<<"can not open file:"<<pwFile;
    d->m_pw="googol123";
  }
  qDebug()<<"password"<<d->m_pw;

  uiInit();
  connect(ui->btn_Admin, SIGNAL(clicked()), this, SLOT(onActionBtnChecked()));
  connect(ui->btn_General, SIGNAL(clicked()), this, SLOT(onActionBtnChecked()));
}
OptUser::~OptUser()
{
  delete ui;
}
void OptUser::uiInit()
{
    Q_D(OptUser);
    ui->pswWidget->setVisible(d->m_isAdmin);
    ui->btn_Admin->setChecked(d->m_isAdmin);
    ui->btn_General->setChecked(!d->m_isAdmin);
}

bool OptUser::optActive()
{
  Q_D(OptUser);
  qDebug()<<"opt user execute active ";
  if (d->m_isAdmin) {
    QString password = ui->lineEdit->text();
    if (password.compare(d->m_pw) == 0) {
        emit usrChange(d->m_isAdmin, ui->box_NeedCheck->isChecked());
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Wrong Password!"), QMessageBox::Ok);
        return false;
    }
  } else {
      emit usrChange(d->m_isAdmin, ui->box_NeedCheck->isChecked());
  }
  return true;
}
bool OptUser::readOpt()
{
  Q_D(OptUser);
  d->m_isAdmin=data("usr","admin",false).toBool();
  qDebug()<<"optusr read opt";

  return true;
}
bool OptUser::writeOpt()
{
  Q_D(OptUser);
  saveData("usr","admin",d->m_isAdmin);
  return true;
}

void OptUser::respondErrorExecute()
{

}

bool OptUser::isAdmin() const
{
  Q_D(const OptUser);
  return d->m_isAdmin;
}

void OptUser::onActionBtnChecked() {
    Q_D(OptUser);
    setModify(true);
    if (ui->btn_Admin->isChecked()) {
        d->m_isAdmin = true;
        ui->pswWidget->setVisible(true);
    } else {
        d->m_isAdmin = false;
        ui->pswWidget->setVisible(false);
    }
}
