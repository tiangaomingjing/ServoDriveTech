#include "optuser.h"
#include "iopt_p.h"
#include "ui_optuser.h"
class OptUserPrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptUser)
public:
  OptUserPrivate();
  ~OptUserPrivate();
  bool m_isAdmin;
  QString m_pw;
};
OptUserPrivate::OptUserPrivate()
{

}
OptUserPrivate::~OptUserPrivate()
{

}

OptUser::OptUser(const QString &optName, QWidget *parent) : IOpt(optName,*new OptUserPrivate,parent),
  ui(new Ui::OptUser)
{
  ui->setupUi(this);
}
OptUser::~OptUser()
{
  delete ui;
}
void OptUser::optActive()
{
  Q_D(OptUser);
}

