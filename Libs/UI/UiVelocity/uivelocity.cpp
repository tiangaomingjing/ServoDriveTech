#include "uivelocity.h"
#include "ui_uivelocity.h"
#include "iuiwidget_p.h"

#include <QQuickWidget>
#include <QQmlContext>

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
  delete ui;
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
  setCurrentUiIndex(0);
}
void UiVelocity::setQmlContext()
{

}

void UiVelocity::setQmlSignalSlot()
{

}

void UiVelocity::addQmlWidget()
{
  Q_D(UiVelocity);
  ui->qmlHboxLayout->addWidget(d->m_qwidget);
}
