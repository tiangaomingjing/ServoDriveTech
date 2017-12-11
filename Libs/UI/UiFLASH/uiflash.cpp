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

}

QStackedWidget *UiFLASH::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
