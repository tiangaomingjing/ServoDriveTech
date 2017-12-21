#include "uiio.h"
#include "ui_uiio.h"
#include "iuiwidget_p.h"

class UiIOPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiIO)
public:
  UiIOPrivate();
  ~UiIOPrivate();
protected:

};
UiIOPrivate::UiIOPrivate()
{

}
UiIOPrivate::~UiIOPrivate()
{

}

UiIO::UiIO(QWidget *parent):IUiWidget(*(new UiIOPrivate),parent),ui(new Ui::UiIO)
{
  ui->setupUi(this);

}
UiIO::~UiIO()
{
  delete ui;
}

QStackedWidget *UiIO::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}

QVBoxLayout *UiIO::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiIO::setDefaultUi()
{
  setCurrentUiIndex(0);
}
