#include "uistatus.h"
#include "ui_uistatus.h"
#include "iuiwidget_p.h"

class UiStatusPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiStatus)
public:
  UiStatusPrivate();
  ~UiStatusPrivate();
protected:
  int test;
};
UiStatusPrivate::UiStatusPrivate()
{

}
UiStatusPrivate::~UiStatusPrivate()
{

}

UiStatus::UiStatus(QWidget *parent):IUiWidget(*(new UiStatusPrivate),parent),ui(new Ui::UiStatus)
{
  ui->setupUi(this);

}
UiStatus::~UiStatus()
{

}

QStackedWidget *UiStatus::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
