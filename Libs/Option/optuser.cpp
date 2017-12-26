﻿#include "optuser.h"
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
  ui->setupUi(this);
  readOptFile();

  Q_D(OptUser);

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
}
OptUser::~OptUser()
{
  delete ui;
}
bool OptUser::optActive()
{
  Q_D(OptUser);
  return true;
}
bool OptUser::readOpt(QSettings *settings)
{
  qDebug()<<"optusr read opt";
  return true;
}
bool OptUser::writeOpt(QSettings *settings)
{
  return true;
}

bool OptUser::isAdmin() const
{
  Q_D(const OptUser);
  return d->m_isAdmin;
}
