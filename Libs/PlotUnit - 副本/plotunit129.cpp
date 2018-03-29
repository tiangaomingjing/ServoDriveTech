#include "plotunit129.h"
#include "ui_plotunit129.h"
#include "iplotunit_p.h"

class PlotUnit129Private:public IPlotUnitPrivate
{
  Q_DECLARE_PUBLIC(PlotUnit129)
public:
  PlotUnit129Private(){}
  ~PlotUnit129Private(){}
protected:

};

PlotUnit129::PlotUnit129(QWidget *parent) :
  IPlotUnit(*(new PlotUnit129Private),parent),
  ui(new Ui::PlotUnit129)
{
  ui->setupUi(this);
  ui->pushButton->setCheckable(true);
  ui->pushButton->setChecked(true);
}

PlotUnit129::~PlotUnit129()
{
  delete ui;
}

void PlotUnit129::on_pushButton_clicked()
{
  Q_D(PlotUnit129);
  emit winFloatingChange(ui->pushButton->isChecked());
}
