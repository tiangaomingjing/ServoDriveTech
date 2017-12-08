#include "uicurrent.h"
#include "ui_uicurrent.h"
#include "iuiwidget_p.h"

class UiCurrentPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiCurrent)
public:
  UiCurrentPrivate();
  ~UiCurrentPrivate();
protected:

};
UiCurrentPrivate::UiCurrentPrivate()
{

}
UiCurrentPrivate::~UiCurrentPrivate()
{

}

UiCurrent::UiCurrent(QWidget *parent):IUiWidget(*(new UiCurrentPrivate),parent),ui(new Ui::UiCurrent)
{
  ui->setupUi(this);
}
UiCurrent::~UiCurrent()
{

}
