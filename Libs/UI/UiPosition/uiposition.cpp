#include "uiposition.h"
#include "ui_uiposition.h"
#include "iuiwidget_p.h"

#include <QQuickWidget>
#include <QQmlContext>

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
QVBoxLayout *UiPosition::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiPosition::setDefaultUi()
{
  setCurrentUiIndex(0);
}
void UiPosition::setQmlContext()
{

}

void UiPosition::setQmlSignalSlot()
{

}

void UiPosition::addQmlWidget()
{
  Q_D(UiPosition);
  ui->qmlHboxLayout->addWidget(d->m_qwidget);
}
