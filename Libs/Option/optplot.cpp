#include "optplot.h"
#include "iopt_p.h"
#include "ui_optplot.h"

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

OptPlot::OptPlot(const QString &optName, QWidget *parent) : IOpt(optName,*new OptPlotPrivate,parent)
{
  ui->setupUi(this);
}
OptPlot::~OptPlot()
{
  delete ui;
}

bool OptPlot::optActive()
{
  return true;
}
