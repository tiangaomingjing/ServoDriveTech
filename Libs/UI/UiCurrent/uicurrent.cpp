#include "uicurrent.h"
#include "ui_uicurrent.h"
#include "iuiwidget_p.h"

#include <QQuickWidget>
#include <QQmlContext>

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
  delete ui;
}

void UiCurrent::addGraphWidget(QWidget *w)
{
  ui->qmlHboxLayout->addWidget(w);
}

QStackedWidget *UiCurrent::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiCurrent::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiCurrent::setDefaultUi()
{
  setCurrentUiIndex(0);
}
void UiCurrent::setQmlContext()
{

}

void UiCurrent::setQmlSignalSlot()
{

}

void UiCurrent::addQmlWidget()
{
  Q_D(UiCurrent);
  ui->qmlHboxLayout->addWidget(d->m_qwidget);
}
