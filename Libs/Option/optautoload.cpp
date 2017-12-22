#include "optautoload.h"
#include "iopt_p.h"
#include "ui_optautoload.h"

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
}
OptAutoLoad::~OptAutoLoad()
{
  delete ui;
}
bool OptAutoLoad::optActive()
{
  return true;
}

