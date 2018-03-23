#include "uiflash.h"
#include "ui_uiflash.h"
#include "iuiwidget_p.h"

class UiFLASHPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiFLASH)
public:
  UiFLASHPrivate();
  ~UiFLASHPrivate();
protected:
};
UiFLASHPrivate::UiFLASHPrivate()
{

}
UiFLASHPrivate::~UiFLASHPrivate()
{

}

UiFLASH::UiFLASH(QWidget *parent):IUiWidget(*(new UiFLASHPrivate),parent),ui(new Ui::UiFLASH)
{
  ui->setupUi(this);

}
UiFLASH::~UiFLASH()
{
  delete ui;
}

bool UiFLASH::hasConfigFunc()
{
  return false;
}

bool UiFLASH::hasSaveFunc()
{
  return false;
}

QStackedWidget *UiFLASH::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiFLASH::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiFLASH::setDefaultUi()
{
  setCurrentUiIndex(1);
}

