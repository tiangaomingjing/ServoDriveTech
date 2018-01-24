#include "formlangtest2.h"
#include "ui_formlangtest2.h"

FormLangTest2::FormLangTest2(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormLangTest2)
{
  ui->setupUi(this);
  ui->label_2->setText(tr("this is text form coding_2"));
  QString lang="D:/Smart/ServoMaster/git-project/ServoDriveTech/ServoDriveTech/App/AppOptionTest/ch_main_test2.qm";
  trans.load(lang);
  qApp->installTranslator(&trans);
  ui->retranslateUi(this);
  ui->label_2->setText(tr("this is text form coding_2"));
//  setAttribute(Qt::WA_DeleteOnClose);   //关闭后自动删除本对象
}

FormLangTest2::~FormLangTest2()
{
  qApp->removeTranslator(&trans);
  delete ui;
}
