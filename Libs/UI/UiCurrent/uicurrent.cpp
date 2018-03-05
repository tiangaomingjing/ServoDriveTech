#include "uicurrent.h"
#include "ui_uicurrent.h"
#include "iuiwidget_p.h"
#include "igraphcurrent.h"

#include <QQuickWidget>
#include <QQmlContext>
#include <QDebug>

class UiCurrentPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiCurrent)
public:
  UiCurrentPrivate();
  ~UiCurrentPrivate();
protected:
  IGraphCurrent *m_graphCurrent;
};
UiCurrentPrivate::UiCurrentPrivate():IUiWidgetPrivate(),
  m_graphCurrent(NULL)
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
  qDebug()<<"begin release UiCurrent ------------------>";
  Q_D(UiCurrent);
  delete d->m_graphCurrent;
  delete ui;

  qDebug()<<"UiCurrent destruct-->";
}

void UiCurrent::accept(QWidget *w)
{
  Q_D(UiCurrent);
  ui->qmlHboxLayout->addWidget(w);
  d->m_graphCurrent=dynamic_cast<IGraphCurrent *>(w);
  d->m_graphCurrent->visit(this);
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
