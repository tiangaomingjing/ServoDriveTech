#include "uibrake.h"
#include "ui_uibrake.h"
#include "iuiwidget_p.h"

class UiBrakePrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiBrake)
public:
  UiBrakePrivate();
  ~UiBrakePrivate();
protected:
  int test;
};
UiBrakePrivate::UiBrakePrivate()
{

}
UiBrakePrivate::~UiBrakePrivate()
{

}

UiBrake::UiBrake(QWidget *parent):IUiWidget(*(new UiBrakePrivate),parent),ui(new Ui::UiBrake)
{
  ui->setupUi(this);

}
UiBrake::~UiBrake()
{

}
QStackedWidget *UiBrake::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiBrake::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiBrake::setDefaultUi()
{
  setCurrentUiIndex(1);
}
