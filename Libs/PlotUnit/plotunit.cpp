#include "plotunit.h"
#include "ui_plotunit.h"

#include <QDebug>
#include <QHBoxLayout>

class PlotUnitPrivate{
public:
  PlotUnitPrivate():isFloating(false)
  {}
  ~PlotUnitPrivate(){}
  bool isFloating;
};

PlotUnit::PlotUnit(QWidget *parent):QWidget(parent),
  ui(new Ui::PlotUnit),
  d(new PlotUnitPrivate)
{
  ui->setupUi(this);
}
PlotUnit::~PlotUnit()
{
  delete ui;
  delete d;
}

void PlotUnit::on_pushButton_clicked()
{
  d->isFloating=!d->isFloating;
  emit floatingChanged(d->isFloating);
  qDebug()<<"is floating "<<d->isFloating;
}
