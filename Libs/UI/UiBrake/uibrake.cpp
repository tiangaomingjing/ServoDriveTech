#include "uibrake.h"
#include "ui_uibrake.h"
#include "iuiwidget_p.h"
#include "sevdevice.h"
#include "igraphbrake.h"

#include <QQuickWidget>
#include <QQmlContext>
#include <QDebug>

class UiBrakePrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiBrake)
public:
  UiBrakePrivate();
  ~UiBrakePrivate();
protected:
  IGraphBrake *m_graphBrake;
};
UiBrakePrivate::UiBrakePrivate():
    m_graphBrake(NULL)
{

}
UiBrakePrivate::~UiBrakePrivate()
{
    delete m_graphBrake;
    qDebug()<<"UiBrakePrivate destruct-->";
}

UiBrake::UiBrake(QWidget *parent):IUiWidget(*(new UiBrakePrivate),parent),ui(new Ui::UiBrake)
{
  ui->setupUi(this);

}
UiBrake::~UiBrake()
{
  delete ui;
}
void UiBrake::accept(QWidget *w)
{
    Q_D(UiBrake);
  ui->qmlHboxLayout->addWidget(w);
  d->m_graphBrake=dynamic_cast<IGraphBrake *>(w);
  d->m_graphBrake->visit(this);
}

void UiBrake::setUiActive(bool actived)
{
  if(actived)
  {
    Q_D(UiBrake);
    if(readGenRAM())
      d->m_graphBrake->syncTreeDataToUiFace();
  }
}
bool UiBrake::writePageFLASH()
{
  Q_D(UiBrake);
  bool wOk=true;
  wOk=IUiWidget::writePageFLASH();
  if(wOk)
  {
    d->m_graphBrake->syncTreeDataToUiFace();
    //还要加入关联参数处理
    //-to add
  }
  return true;
}

bool UiBrake::hasConfigFunc()
{
  return false;
}

bool UiBrake::hasSaveFunc()
{
  return true;
}

QStackedWidget *UiBrake::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiBrake::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiBrake::setDefaultUi()
{
  setCurrentUiIndex(0);
}

