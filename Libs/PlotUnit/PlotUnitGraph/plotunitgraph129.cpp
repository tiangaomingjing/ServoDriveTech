#include "plotunitgraph129.h"
#include "ui_plotunitgraph129.h"
#include "iplotunitgraph_p.h"

class PlotUnitGraph129Private:public IPlotUnitGraphPrivate
{
  Q_DECLARE_PUBLIC(PlotUnitGraph129)
public:
  PlotUnitGraph129Private(){}
  ~PlotUnitGraph129Private(){}
protected:

};

PlotUnitGraph129::PlotUnitGraph129(QWidget *parent) :
  IPlotUnitGraph(*(new PlotUnitGraph129Private),parent),
  ui(new Ui::PlotUnitGraph129)
{
  ui->setupUi(this);
}

PlotUnitGraph129::~PlotUnitGraph129()
{
  delete ui;
}
