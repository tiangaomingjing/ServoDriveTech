#include "uistatus.h"
#include "ui_uistatus.h"
#include "iuiwidget_p.h"

#include <QQuickWidget>
#include <QQmlContext>

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
  delete ui;
}
void UiStatus::accept(QWidget *w)
{
  ui->qmlHboxLayout->addWidget(w);
}

QStackedWidget *UiStatus::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiStatus::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiStatus::setDefaultUi()
{
  setCurrentUiIndex(0);
}
void UiStatus::setQmlContext()
{

}

void UiStatus::setQmlSignalSlot()
{

}

void UiStatus::addQmlWidget()
{
  Q_D(UiStatus);
  ui->qmlHboxLayout->addWidget(d->m_qwidget);
}
