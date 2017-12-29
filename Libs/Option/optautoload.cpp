#include "optautoload.h"
#include "iopt_p.h"
#include "ui_optautoload.h"

#include <QDebug>
#include <QTimer>
#include <QMessageBox>

class OptAutoLoadPrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptAutoLoad)
public:
  OptAutoLoadPrivate();
  ~OptAutoLoadPrivate();
  bool m_auto;
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

  uiInit();

  connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(onCheckedBoxClicked()));
}
OptAutoLoad::~OptAutoLoad()
{
  delete ui;
}
void OptAutoLoad::uiInit()
{
  Q_D(OptAutoLoad);
  ui->checkBox->setChecked(d->m_auto);
}

bool OptAutoLoad::optActive()
{
  Q_D(OptAutoLoad);
  d->m_auto=ui->checkBox->isChecked();
  qDebug()<<"opt auto load execute active ";
//  return false;//test pass
  return true;
}
bool OptAutoLoad::readOpt()
{
  Q_D(OptAutoLoad);
  d->m_auto=data("autoload","auto",false).toBool();
  qDebug()<<"optautoload read opt";

  return true;
}
bool OptAutoLoad::writeOpt()
{
  Q_D(OptAutoLoad);
  saveData("autoload","auto",d->m_auto);
  return true;
}
void OptAutoLoad::respondErrorExecute()
{
  QTimer::singleShot(100,this,SLOT(onRespondErrorExe()));
}

void OptAutoLoad::onCheckedBoxClicked()
{
  setModify(true);
  qDebug()<<"check box clicked";
}

void OptAutoLoad::onRespondErrorExe()
{
  QMessageBox::warning(0,"error","error");
  qDebug()<<"error test";
}
