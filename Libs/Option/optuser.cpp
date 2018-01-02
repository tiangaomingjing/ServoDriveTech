#include "optuser.h"
#include "iopt_p.h"
#include "ui_optuser.h"
#include "gtutils.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>
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
}
OptUser::~OptUser()
{
  delete ui;
}
void OptUser::uiInit()
{

}

bool OptUser::optActive()
{
//  Q_D(OptUser);
  qDebug()<<"opt user execute active ";
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
//  Q_D(OptUser);
//  saveData("usr","admin",d->m_isAdmin);
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
