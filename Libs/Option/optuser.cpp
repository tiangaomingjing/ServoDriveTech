#include "optuser.h"
#include "iopt_p.h"
#include "ui_optuser.h"
#include "gtutils.h"
//#include "ui_usercheckwidgetprivate.h"

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
  bool m_checkShown;
  bool m_isChecked;
  QString m_pw;
};
OptUserPrivate::OptUserPrivate():m_isAdmin(false),m_pw("")
{

}
OptUserPrivate::~OptUserPrivate()
{

}

//class UserCheckWidgetPrivate : public QWidget
//{
//    //Q_OBJECT
//    Q_DECLARE_PUBLIC(QWidget)
//public:
//    explicit UserCheckWidgetPrivate(QWidget *parent = 0);
//    ~UserCheckWidgetPrivate();

//private:
//    Ui::UserCheckWidgetPrivate *ui;
//};

//UserCheckWidgetPrivate::UserCheckWidgetPrivate(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::UserCheckWidgetPrivate)
//{
//    ui->setupUi(this);
//}

//UserCheckWidgetPrivate::~UserCheckWidgetPrivate()
//{
//    delete ui;
//}

OptUser::OptUser(const QString &optName, QWidget *parent) : IOpt(optName,*new OptUserPrivate,parent),
  ui(new Ui::OptUser)
{
  Q_D(OptUser);
  ui->setupUi(this);
  ui->lineEdit->setEchoMode(QLineEdit::Password);
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
  m_page = new UserCheckWidgetPrivate;
  uiInit();
  connect(ui->btn_Admin, SIGNAL(clicked()), this, SLOT(onActionBtnChecked()));
  connect(ui->btn_General, SIGNAL(clicked()), this, SLOT(onActionBtnChecked()));
  connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(onActionLineChange()));
}
OptUser::~OptUser()
{
  delete ui;
}
void OptUser::uiInit()
{
    Q_D(OptUser);
    setModify(false);
    //ui->box_NeedCheck->setVisible(d->m_checkShown);
    m_page->setCheck(d->m_isChecked);
    connect(m_page, SIGNAL(stateChanged()), this, SLOT(onActionLineChange()));
    //d->m_page->setParent(this);
    if (ui->tabWidget->count() == 1) {
        d->m_checkShown = false;
    } else {
        d->m_checkShown = true;
    }
    ui->tabWidget->updatesEnabled();
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
            ui->lineEdit->setReadOnly(true);
            if (d->m_checkShown) {
                qDebug()<<m_page->getPsw();
                if (m_page->getPsw().compare(d->m_pw) == 0) {
                    d->m_isChecked = m_page->isChecked();
                } else {
                    QMessageBox::warning(this, tr("Warning"), tr("Wrong Need Check Password!"), QMessageBox::Ok);
                    return false;
                }
            } else {
                ui->tabWidget->addTab(m_page, "Check");
                d->m_checkShown = true;
                emit usrChange(d->m_isAdmin);
                //ui->box_NeedCheck->setVisible(d->m_checkShown);
            }
        } else {
            ui->lineEdit->clear();
            QMessageBox::warning(this, tr("Warning"), tr("Wrong Password!"), QMessageBox::Ok);
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
  d->m_isChecked = data("usr", "check", true).toBool();
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

bool OptUser::isChecked() const {
    Q_D(const OptUser);
    return d->m_isChecked;
}

void OptUser::onActionBtnChecked() {
    Q_D(OptUser);
    setModify(true);
    if (ui->btn_Admin->isChecked()) {
        d->m_isAdmin = true;
        ui->pswWidget->setVisible(true);
    } else {
        d->m_isAdmin = false;
        d->m_checkShown = false;
        ui->lineEdit->clear();
        ui->lineEdit->setReadOnly(false);
        ui->pswWidget->setVisible(false);
        //ui->box_NeedCheck->setVisible(d->m_checkShown);
        if (ui->tabWidget->count() > 1) {
            m_page->setCheck(d->m_isChecked);
            ui->tabWidget->removeTab(1);
        }
    }
}

void OptUser::onActionLineChange() {
    qDebug()<<"s";
    setModify(true);
}
