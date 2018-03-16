#include "uipower.h"
#include "ui_uipower.h"
#include "iuiwidget_p.h"
#include "sevdevice.h"
#include "igraphpower.h"

#include <QQuickWidget>
#include <QQmlContext>
#include <QDebug>

class UiPowerPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiPower)
public:
  UiPowerPrivate();
  ~UiPowerPrivate();
protected:
  IGraphPower *m_graphPower;
};
UiPowerPrivate::UiPowerPrivate():
    m_graphPower(NULL)
{

}
UiPowerPrivate::~UiPowerPrivate()
{
    delete m_graphPower;
}

UiPower::UiPower(QWidget *parent):IUiWidget(*(new UiPowerPrivate),parent),ui(new Ui::UiPower)
{
  ui->setupUi(this);

}
UiPower::~UiPower()
{
  delete ui;
}

void UiPower::accept(QWidget *w)
{
    Q_D(UiPower);
    ui->qmlHboxLayout->addWidget(w);
    d->m_graphPower=dynamic_cast<IGraphPower *>(w);
    d->m_graphPower->visit(this);
}

void UiPower::setUiActive(bool actived)
{
  if(actived)
  {
    Q_D(UiPower);
    if(readPageFLASH())
      d->m_graphPower->syncTreeDataToUiFace();
  }
}

bool UiPower::writePageFLASH()
{
  Q_D(UiPower);
  bool wOk=true;
  wOk=IUiWidget::writePageFLASH();
  if(wOk)
  {
    d->m_graphPower->syncTreeDataToUiFace();
    //还要加入关联参数处理
    //-to add
  }
  return true;
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
  setCurrentUiIndex(0);
}
