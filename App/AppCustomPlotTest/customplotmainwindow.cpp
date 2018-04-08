#include "customplotmainwindow.h"
#include "ui_customplotmainwindow.h"
#include "gtplot.h"

#include <QDebug>

CustomPlotMainWindow::CustomPlotMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CustomPlotMainWindow)
{
  ui->setupUi(this);

  plot=new GtPlot(ui->widget_2);
  QHBoxLayout *hlayout=new QHBoxLayout(ui->widget_2);
  hlayout->addWidget(plot);
  ui->widget_2->setLayout(hlayout);
  setupSimpleDemo(plot);

  connect(plot,SIGNAL(currentPosChanged(QPointF)),this,SLOT(onPlotPosChanged(QPointF)));
  connect(plot,SIGNAL(horizMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onHtagPosChanged(qreal,qreal,qreal)));
  connect(plot,SIGNAL(vertiMeaDataChanged(qreal,qreal,qreal)),this,SLOT(onVtagPosChanged(qreal,qreal,qreal)));
}

CustomPlotMainWindow::~CustomPlotMainWindow()
{
  qDebug()<<"CustomPlotMainWindow destruct-->";
//  delete plot;
  delete ui;
}


void CustomPlotMainWindow::setupSimpleDemo(QCustomPlot *customPlot)
{
  // add two new graphs and set their look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
  // generate some points of data (y0 for first, y1 for second graph):
  QVector<double> x(251), y0(251), y1(251);
  for (int i=0; i<251; ++i)
  {
    x[i] = i;
    y0[i] = 100*qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
    y1[i] = 100*qExp(-i/150.0);              // exponential envelope
  }
  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  customPlot->graph(1)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );

  customPlot->setSelectionRectMode(QCP::srmNone);

  QCPItemStraightLine *line=new QCPItemStraightLine(customPlot);
  line->setSelectable(true);
  customPlot->setInteraction(QCP::iSelectItems,true);
  customPlot->setInteraction(QCP::iMultiSelect,true);

  QCPItemText *text=new QCPItemText(customPlot);
  text->setText("hello");
  text->position->setType(QCPItemPosition::ptPlotCoords);
  text->position->setCoords(50,100);
}

void CustomPlotMainWindow::on_actionFix_triggered()
{
    plot->rescaleAxes();
    plot->replot();
}


void CustomPlotMainWindow::onPlotPosChanged(const QPointF &point)
{
  ui->label_xy->setText(QString("X:%1,Y:%2").arg(point.x()).arg(point.y()));
}

void CustomPlotMainWindow::onVtagPosChanged(qreal v1, qreal v2, qreal dv)
{
  ui->label_vertical->setText(QString("t1:%1,t2:%2 dy:%3").arg(v1).arg(v2).arg(dv));
}

void CustomPlotMainWindow::onHtagPosChanged(qreal v1, qreal v2, qreal dv)
{
  ui->label_horizontal->setText(QString("t1:%1,t2:%2 dx:%3").arg(v1).arg(v2).arg(dv));
}


void CustomPlotMainWindow::on_actionHMea_triggered(bool checked)
{
    if(checked)
      plot->createHorizMea();
    else
      plot->clearHorizMea();
}


void CustomPlotMainWindow::on_actionVMea_triggered(bool checked)
{
    if(checked)
      plot->createVertiMea();
    else
      plot->clearVertiMea();
}
