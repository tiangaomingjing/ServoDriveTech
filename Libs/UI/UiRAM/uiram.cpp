#include "uiram.h"
#include "ui_uiram.h"
#include "iuiwidget_p.h"

class UiRAMPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiRAM)
public:
  UiRAMPrivate();
  ~UiRAMPrivate();
protected:
  int test;
};
UiRAMPrivate::UiRAMPrivate()
{

}
UiRAMPrivate::~UiRAMPrivate()
{

}

UiRAM::UiRAM(QWidget *parent):IUiWidget(*(new UiRAMPrivate),parent),ui(new Ui::UiRAM)
{
  ui->setupUi(this);

}
UiRAM::~UiRAM()
{
  delete ui;
}

bool UiRAM::hasConfigFunc()
{
  return false;
}

bool UiRAM::hasSaveFunc()
{
  return false;
}

QStackedWidget *UiRAM::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiRAM::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiRAM::setDefaultUi()
{
  setCurrentUiIndex(1);
}
