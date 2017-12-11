#include "uiposition.h"
#include "ui_uiposition.h"
#include "iuiwidget_p.h"

class UiPositionPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiPosition)
public:
  UiPositionPrivate();
  ~UiPositionPrivate();
protected:
  int test;
};
UiPositionPrivate::UiPositionPrivate()
{

}
UiPositionPrivate::~UiPositionPrivate()
{

}

UiPosition::UiPosition(QWidget *parent):IUiWidget(*(new UiPositionPrivate),parent),ui(new Ui::UiPosition)
{
  ui->setupUi(this);

}
UiPosition::~UiPosition()
{

}

QStackedWidget *UiPosition::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
