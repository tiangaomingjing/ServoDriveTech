#include "uiplot.h"
#include "ui_uiplot.h"
#include "iuiwidget_p.h"
#include "iplotunit.h"

#include <QDebug>

class UiPlotPrivate:public IUiWidgetPrivate
{
  Q_DECLARE_PUBLIC(UiPlot)
public:
  UiPlotPrivate();
  ~UiPlotPrivate();
protected:
  IPlotUnit *m_iplotUint;
};
UiPlotPrivate::UiPlotPrivate()
{

}
UiPlotPrivate::~UiPlotPrivate()
{

}


UiPlot::UiPlot(QWidget *parent):IUiWidget(*(new UiPlotPrivate),parent),ui(new Ui::UiPlot)
{
  ui->setupUi(this);

}
UiPlot::~UiPlot()
{
  Q_D(UiPlot);
  delete d->m_iplotUint;
  delete ui;
}

void UiPlot::accept(QWidget *w)
{
  Q_D(UiPlot);
  d->m_iplotUint=dynamic_cast<IPlotUnit *>(w);
  ui->qmlHboxLayout->addWidget(d->m_iplotUint);
  d->m_iplotUint->visit(this);
  connect(d->m_iplotUint,SIGNAL(winFloatingChange(bool)),this,SLOT(onWinFloatChanged(bool)));
}

QStackedWidget *UiPlot::getUiStackedWidget(void)
{
  return ui->stackedWidget;
}
QVBoxLayout *UiPlot::getVBoxLayout(void)
{
  return ui->verticalLayout_tree;
}
void UiPlot::setDefaultUi()
{
  setCurrentUiIndex(0);
}

QHBoxLayout *UiPlot::hBoxLayout()
{
  return ui->qmlHboxLayout;
}

void UiPlot::setUiActive(bool actived)
{
  Q_D(UiPlot);
  d->m_iplotUint->respondUiActive(actived);
}

void UiPlot::onWinFloatChanged(bool isIn)
{
  Q_D(UiPlot);
  qDebug()<<"win float is in"<<isIn;
  if(isIn)
  {
    ui->qmlHboxLayout->addWidget(d->m_iplotUint);
    d->m_iplotUint->show();

  }
  else
  {
    ui->qmlHboxLayout->removeWidget(d->m_iplotUint);
    d->m_iplotUint->setParent(0);
    d->m_iplotUint->showMaximized();
  }
}
