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
  delete m_graphMotor;
  qDebug()<<"UiMotorPrivate destruct-->";
}

UiMotor::UiMotor(QWidget *parent):IUiWidget(*(new UiMotorPrivate),parent),ui(new Ui::UiMotor)
{
  ui->setupUi(this);

}
UiMotor::~UiMotor()
{
  delete ui;
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
void UiMotor::setQmlContext()
{

}

void UiMotor::setQmlSignalSlot()
{

}

void UiMotor::addQmlWidget()
{
  Q_D(UiMotor);
  ui->qmlHboxLayout->addWidget(d->m_qwidget);
}
void UiMotor::updateUi()
{
  readPageFLASH();
}
