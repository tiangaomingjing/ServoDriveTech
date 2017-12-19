#include "uivelocity.h"
#include "ui_uivelocity.h"
#include "iuiwidget_p.h"

class UiVelocityPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiVelocity)
public:
  UiVelocityPrivate();
  ~UiVelocityPrivate();
protected:
  int test;
};
UiVelocityPrivate::UiVelocityPrivate()
{

}
UiVelocityPrivate::~UiVelocityPrivate()
{

}


UiVelocity::UiVelocity(QWidget *parent):IUiWidget(*(new UiVelocityPrivate),parent),ui(new Ui::UiVelocity)
{
  ui->setupUi(this);

}
UiVelocity::~UiVelocity()
{

}

QStackedWidget *UiVelocity::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}

QVBoxLayout *UiVelocity::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiVelocity::setDefaultUi()
{
  setCurrentUiIndex(1);
}
