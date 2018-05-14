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
  double m_xStoreTime;
  double m_xDisplayTime;
  double m_yMax;
  double m_yMin;
  double m_storedTime;
  quint16 m_pointNum;
  QString m_color;
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
  QStringList list;
  list<<"gray"<<"white"<<"black"<<"darkGray"<<"blue"<<"lightGray"<<"lightBlack";
  ui->comboBox_plotColor->addItems(list);
  readOpt();
  uiInit();


  connect(ui->spinBox_plotDelay, SIGNAL(valueChanged(int)), this, SLOT(valueModified()));
  connect(ui->doubleSpinBox_plotXDisplayTime, SIGNAL(valueChanged(double)), this, SLOT(valueModified()));
  connect(ui->doubleSpinBox_ployYMax, SIGNAL(valueChanged(double)), this, SLOT(valueModified()));
  connect(ui->doubleSpinBox_plotYMin, SIGNAL(valueChanged(double)), this, SLOT(valueModified()));
  connect(ui->doubleSpinBox_plotStore, SIGNAL(valueChanged(double)), this, SLOT(valueModified()));
  connect(ui->spinBox_plotPoint, SIGNAL(valueChanged(int)), this, SLOT(valueModified()));
  connect(ui->comboBox_plotColor, SIGNAL(currentIndexChanged(int)), this, SLOT(valueModified()));
}
OptPlot::~OptPlot()
{
  delete ui;
}
void OptPlot::uiInit()
{
    Q_D(OptPlot);
    qDebug()<<"plot ui Init";
    ui->spinBox_plotDelay->setValue(d->m_delayTime);
    ui->doubleSpinBox_plotXDisplayTime->setValue(d->m_xDisplayTime);
    ui->doubleSpinBox_plotXStoreTime->setValue(d->m_xStoreTime);
    ui->doubleSpinBox_ployYMax->setValue(d->m_yMax);
    ui->doubleSpinBox_plotYMin->setValue(d->m_yMin);
    ui->doubleSpinBox_plotStore->setValue(d->m_storedTime);
    ui->spinBox_plotPoint->setValue(d->m_pointNum);
    ui->comboBox_plotColor->setCurrentText(d->m_color);
}

quint16 OptPlot::delayTime()
{
    Q_D(OptPlot);
  return d->m_delayTime;
}

double OptPlot::xStoreTime()
{
  Q_D(OptPlot);
  return d->m_xStoreTime;
}

double OptPlot::xDisplayTime()
{
    Q_D(OptPlot);
    return d->m_xDisplayTime;
}

double OptPlot::yMax()
{
    Q_D(OptPlot);
    return d->m_yMax;
}

double OptPlot::yMin()
{
    Q_D(OptPlot);
    return d->m_yMin;
}

double OptPlot::storedTime()
{
    Q_D(OptPlot);
    return d->m_storedTime;
}

quint16 OptPlot::pointNum()
{
    Q_D(OptPlot);
    return d->m_pointNum;
}

QString OptPlot::plotColor()
{
    Q_D(OptPlot);
    return d->m_color;
}

bool OptPlot::optActive()
{
    Q_D(OptPlot);
  qDebug()<<"opt plot execute active ";
    d->m_delayTime = ui->spinBox_plotDelay->value();
    d->m_xStoreTime = ui->doubleSpinBox_plotXStoreTime->value();
    d->m_xDisplayTime = ui->doubleSpinBox_plotXDisplayTime->value();
    d->m_yMax = ui->doubleSpinBox_ployYMax->value();
    d->m_yMin = ui->doubleSpinBox_plotYMin->value();
    d->m_storedTime = ui->doubleSpinBox_plotStore->value();
    d->m_pointNum = ui->spinBox_plotPoint->value();
    d->m_color = ui->comboBox_plotColor->currentText();
    emit plotParametersChanged();
  return true;
}
bool OptPlot::readOpt()
{
  Q_D(OptPlot);
  d->m_delayTime=data("plot","delayTime",1000).toUInt();
  d->m_xStoreTime = data("plot","xStoreTime",20).toDouble();
  d->m_xDisplayTime = data("plot", "xDisplayTime", 5.00).toDouble();
  d->m_yMax = data("plot", "yMax", 5000.00).toDouble();
  d->m_yMin = data("plot", "yMin", -500.00).toDouble();
  d->m_storedTime = data("plot", "storeTime", 60).toDouble();
  d->m_pointNum = data("plot", "pointAmount", 1000).toUInt();
  d->m_color = data("plot", "color", "white").toString();
  qDebug()<<"optplot read opt";
  return true;
}
bool OptPlot::writeOpt()
{
  Q_D(OptPlot);
  saveData("plot","delayTime",d->m_delayTime);
  saveData("plot","xStoreTime",d->m_xStoreTime);
  saveData("plot", "xDisplayTime", d->m_xDisplayTime);
  saveData("plot", "yMax", d->m_yMax);
  saveData("plot", "yMin", d->m_yMin);
  saveData("plot", "storeTime", d->m_storedTime);
  saveData("plot", "pointAmount", d->m_pointNum);
  saveData("plot", "color", d->m_color);
  return true;
}
void OptPlot::respondErrorExecute()
{

}

void OptPlot::valueModified()
{
   setModify(true);
}
