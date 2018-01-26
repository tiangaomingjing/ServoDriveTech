#include "formlangtest1.h"
#include "ui_formlangtest1.h"

FormLangTest1::FormLangTest1(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormLangTest1)
{
  ui->setupUi(this);
  ui->label_2->setText(tr("this is text form coding_1"));
  QString lang="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/App/AppOptionTest/ch_main_test.qm";
  trans.load(lang);
  qApp->installTranslator(&trans);
  ui->retranslateUi(this);
  ui->label_2->setText(tr("this is text form coding_1"));
//  setAttribute(Qt::WA_DeleteOnClose);   //关闭后自动删除本对象
}

FormLangTest1::~FormLangTest1()
{
  qApp->removeTranslator(&trans);
  delete ui;
}
