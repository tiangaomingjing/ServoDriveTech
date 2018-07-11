#include "uimotor.h"
#include "ui_uimotor.h"
#include "iuiwidget_p.h"
#include "sevdevice.h"
#include "igraphmotor.h"

#include <QQuickWidget>
#include <QQmlContext>
#include <QDebug>


class UiMotorPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiMotor)
public:
  UiMotorPrivate();
  ~UiMotorPrivate();

protected:
  IGraphMotor *m_graphMotor;
};

UiMotorPrivate::UiMotorPrivate():
  m_graphMotor(NULL)
{

}
UiMotorPrivate::~UiMotorPrivate()
{
  qDebug()<<"UiMotorPrivate destruct-->";
}

UiMotor::UiMotor(QWidget *parent):IUiWidget(*(new UiMotorPrivate),parent),ui(new Ui::UiMotor)
{
  ui->setupUi(this);

}
UiMotor::~UiMotor()
{
  Q_D(UiMotor);
  delete ui;
  delete d->m_graphMotor;
}

//!
//! \brief UiMotor::accept take owership of (w)
//! \param w
//!
void UiMotor::accept(QWidget *w)
{
  Q_D(UiMotor);
  ui->qmlHboxLayout->addWidget(w);
  d->m_graphMotor=dynamic_cast<IGraphMotor *>(w);
  d->m_graphMotor->visit(this);
}
void UiMotor::setUiActive(bool actived)
{
  if(actived)
  {
    Q_D(UiMotor);
    if(readPageFLASH())
      d->m_graphMotor->syncTreeDataToUiFace();
  }
}
bool UiMotor::writePageFLASH()
{
  Q_D(UiMotor);
  bool wOk=true;
  wOk=IUiWidget::writePageFLASH();
  if(wOk)
  {
    d->m_graphMotor->syncTreeDataToUiFace();
    //还要加入关联参数处理
    //-to add
    d->m_device->imaxPrmAssociationActive(d->m_index.axisInx);
  }
  return true;
}

bool UiMotor::hasConfigFunc()
{
  return false;
}

bool UiMotor::hasSaveFunc()
{
  return true;
}

void UiMotor::setContextAction()
{
  createActionSwitchView();
}

QStackedWidget *UiMotor::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiMotor::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiMotor::setDefaultUi()
{
  setCurrentUiIndex(0);
}

