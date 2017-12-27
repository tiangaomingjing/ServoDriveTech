#include "optautoload.h"
#include "iopt_p.h"
#include "ui_optautoload.h"

#include <QDebug>

class OptAutoLoadPrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptAutoLoad)
public:
  OptAutoLoadPrivate();
  ~OptAutoLoadPrivate();
};

OptAutoLoadPrivate::OptAutoLoadPrivate()
{

}
OptAutoLoadPrivate::~OptAutoLoadPrivate()
{

}
OptAutoLoad::OptAutoLoad(const QString &optName, QWidget *parent) : IOpt(optName,*new OptAutoLoadPrivate,parent),
  ui(new Ui::OptAutoLoad)
{
  ui->setupUi(this);
  readOpt();
}
OptAutoLoad::~OptAutoLoad()
{
  delete ui;
}
bool OptAutoLoad::optActive()
{
  return true;
}
bool OptAutoLoad::readOpt()
{
  qDebug()<<"optautoload read opt";
  return true;
}
bool OptAutoLoad::writeOpt()
{
  return true;
}

