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
  bool m_checkShown;
  bool m_isChecked;
  QString m_pw;
  UserCheckWidgetPrivate* m_page;
  QString m_errMsg;
};
OptUserPrivate::OptUserPrivate():m_isAdmin(false),m_pw("")
{

}
OptUserPrivate::~OptUserPrivate()
{

}

UserCheckWidgetPrivate::UserCheckWidgetPrivate(QWidget *parent) :
    QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    checkBox = new QCheckBox(this);
    checkBox->setObjectName(QStringLiteral("checkBox"));

    gridLayout->addWidget(checkBox, 0, 0, 1, 2);

    horizontalSpacer = new QSpacerItem(249, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));

    gridLayout->addWidget(label, 1, 0, 1, 1);

    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));

    gridLayout->addWidget(lineEdit, 1, 1, 1, 2);

    verticalSpacer = new QSpacerItem(20, 205, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);
    checkBox->setText(QApplication::translate("UserCheckWidgetPrivate", "CheckBox", 0));
    label->setText(QApplication::translate("UserCheckWidgetPrivate", "Password:", 0));

    lineEdit->setEchoMode(QLineEdit::Password);
    connect(checkBox, SIGNAL(clicked()), this, SLOT(onStateChanged()));
}

UserCheckWidgetPrivate::~UserCheckWidgetPrivate()
{

}

void UserCheckWidgetPrivate::setCheck(bool isChecked) {
    checkBox->setChecked(isChecked);
}

bool UserCheckWidgetPrivate::isChecked() {
    return checkBox->isChecked();
}

QString UserCheckWidgetPrivate::getPsw() {
    return lineEdit->text();
}

void UserCheckWidgetPrivate::onStateChanged() {
    qDebug()<<"ss";
    emit stateChanged();
}

void UserCheckWidgetPrivate::pswClear() {
    lineEdit->clear();
}


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
  d->m_page = new UserCheckWidgetPrivate;
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
    d->m_page->setCheck(d->m_isChecked);
    connect(d->m_page, SIGNAL(stateChanged()), this, SLOT(onActionLineChange()));
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
                qDebug()<<d->m_page->getPsw();
                if (d->m_page->getPsw().compare(d->m_pw) == 0) {
                    d->m_isChecked = d->m_page->isChecked();
                } else {
                    d->m_errMsg = "Wrong Need Check Password!";
                    //QMessageBox::warning(this, tr("Warning"), tr("Wrong Need Check Password!"), QMessageBox::Ok);
                    return false;
                }
            } else {
                ui->tabWidget->addTab(d->m_page, "Check");
                d->m_checkShown = true;
                emit usrChange(d->m_isAdmin);
                //ui->box_NeedCheck->setVisible(d->m_checkShown);
            }
        } else {
            ui->lineEdit->clear();
            d->m_errMsg = "Wrong Password!";
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
    Q_D(OptUser);
    QMessageBox::warning(this, tr("Warning"), d->m_errMsg, QMessageBox::Ok);
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
        d->m_page->pswClear();
        ui->lineEdit->setReadOnly(false);
        ui->pswWidget->setVisible(false);
        //ui->box_NeedCheck->setVisible(d->m_checkShown);
        if (ui->tabWidget->count() > 1) {
            d->m_page->setCheck(d->m_isChecked);
            ui->tabWidget->removeTab(1);
        }
    }
}

void OptUser::onActionLineChange() {
    qDebug()<<"s";
    setModify(true);
}
