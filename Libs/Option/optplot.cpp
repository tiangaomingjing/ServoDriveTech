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
  readOptFile();
}
OptPlot::~OptPlot()
{
  delete ui;
}

bool OptPlot::optActive()
{
  return true;
}
bool OptPlot::readOpt(QSettings *settings)
{
  qDebug()<<"optplot read opt";
  return true;
}
bool OptPlot::writeOpt(QSettings *settings)
{
  return true;
}
