#include "optplot.h"
#include "iopt_p.h"
#include "ui_optplot.h"

#include <QDebug>

class OptPlotPrivate:public IOptPrivate
{
  Q_DECLARE_PUBLIC(OptPlot)
public:
  OptPlotPrivate();
  ~OptPlotPrivate();
  quint16 m_delayTime;
};
OptPlotPrivate::OptPlotPrivate()
{

}
OptPlotPrivate::~OptPlotPrivate()
{

}

OptPlot::OptPlot(const QString &optName, QWidget *parent) : IOpt(optName,*new OptPlotPrivate,parent),
  ui(new Ui::OptPlot)
{
  ui->setupUi(this);
  readOpt();
  uiInit();
}
OptPlot::~OptPlot()
{
  delete ui;
}
void OptPlot::uiInit()
{
    qDebug()<<"plot ui Init";
}

bool OptPlot::optActive()
{
  qDebug()<<"opt plot execute active ";
  return true;
}
bool OptPlot::readOpt()
{
  Q_D(OptPlot);
  d->m_delayTime=data("plot","delayTime",500).toUInt();
  qDebug()<<"optplot read opt";
  return true;
}
bool OptPlot::writeOpt()
{
  Q_D(OptPlot);
  saveData("plot","delayTime",d->m_delayTime);
  return true;
}
void OptPlot::respondErrorExecute()
{

}
