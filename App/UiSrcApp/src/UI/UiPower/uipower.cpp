﻿#include "uipower.h"
#include "ui_uipower.h"
#include "iuiwidget_p.h"

class UiPowerPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiPower)
public:
  UiPowerPrivate();
  ~UiPowerPrivate();
protected:
};
UiPowerPrivate::UiPowerPrivate()
{

}
UiPowerPrivate::~UiPowerPrivate()
{

}

UiPower::UiPower(QWidget *parent):IUiWidget(*(new UiPowerPrivate),parent),ui(new Ui::UiPower)
{
  ui->setupUi(this);

}
UiPower::~UiPower()
{

}

QStackedWidget *UiPower::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}

QVBoxLayout *UiPower::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiPower::setDefaultUi()
{
  setCurrentUiIndex(1);
}
