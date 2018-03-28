#include "uistatus.h"
#include "ui_uistatus.h"
#include "iuiwidget_p.h"
#include "igraphstatus.h"
#include "sevdevice.h"

#include <QQuickWidget>
#include <QQmlContext>

class UiStatusPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiStatus)
public:
  UiStatusPrivate();
  ~UiStatusPrivate();
protected:
  IGraphStatus *m_graphStatus;
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
  Q_D(UiStatus);
  ui->qmlHboxLayout->addWidget(w);

  d->m_graphStatus=dynamic_cast<IGraphStatus *>(w);
  d->m_graphStatus->visit(this);
}
void UiStatus::setUiActive(bool actived)
{
  Q_D(UiStatus);
  if(d->m_device->isConnecting())
   d->m_graphStatus->setTimerActive(actived);
  else
    d->m_graphStatus->setTimerActive(false);
}

bool UiStatus::hasConfigFunc()
{
  return false;
}

bool UiStatus::hasSaveFunc()
{
  return false;
}

void UiStatus::setContextAction()
{
  createActionSwitchView();
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

