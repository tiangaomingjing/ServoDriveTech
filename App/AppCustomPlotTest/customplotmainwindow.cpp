#include "customplotmainwindow.h"
#include "ui_customplotmainwindow.h"
#include "gtplot.h"

#include <QDebug>

CustomPlotMainWindow::CustomPlotMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CustomPlotMainWindow)
{
  ui->setupUi(this);
  setupSimpleDemo(ui->customplot);
  ui->customplot->setMouseTracking(true);

  GtPlot *plot=new GtPlot(ui->widget_2);
  QHBoxLayout *hlayout=new QHBoxLayout(ui->widget_2);
  hlayout->addWidget(plot);
  ui->widget_2->setLayout(hlayout);
  setupSimpleDemo(plot);
  connect(ui->customplot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(onPlotMouseMoveEvent(QMouseEvent*)));
  connect(ui->customplot,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(onPlotMousePressEvent(QMouseEvent*)));
  connect(ui->customplot,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(onPlotMouseReleaseEvent(QMouseEvent*)));

  connect(plot,SIGNAL(currentPosChanged(QPointF)),this,SLOT(onPlotPosChanged(QPointF)));
  connect(plot->htag,SIGNAL(currentDataChanged(qreal)),this,SLOT(onHtagPosChanged(qreal)));
  connect(plot->vtag,SIGNAL(currentDataChanged(qreal)),this,SLOT(onVtagPosChanged(qreal)));
}

CustomPlotMainWindow::~CustomPlotMainWindow()
{
  delete ui;
}

void CustomPlotMainWindow::keyPressEvent(QKeyEvent *event)
{
  qDebug()<<"key"<<event->key();
  static bool zoom=false;
  if(event->key()==Qt::Key_Shift)
  {
    if(!zoom)
      ui->customplot->setSelectionRectMode(QCP::srmZoom);
    else
      ui->customplot->setSelectionRectMode(QCP::srmNone);
    zoom=!zoom;
  }
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
}

void CustomPlotMainWindow::on_actionFix_triggered()
{
    ui->customplot->rescaleAxes();
    ui->customplot->replot();
}

void CustomPlotMainWindow::onPlotMouseMoveEvent(QMouseEvent *event)
{
//  if((event->buttons()&Qt::LeftButton)&&QApplication::keyboardModifiers()==Qt::ControlModifier)
//  {
//    ui->customplot->setSelectionRectMode(QCP::srmZoom);
//    qDebug()<<"srmZoom";
//  }
//  qDebug()<<event->pos();
}

void CustomPlotMainWindow::onPlotMousePressEvent(QMouseEvent *event)
{
  qDebug()<<"press";
  if((event->button()==Qt::LeftButton)&&(QApplication::keyboardModifiers()==Qt::ControlModifier))
  {
    ui->customplot->setSelectionRectMode(QCP::srmZoom);

    qDebug()<<"srmZoom"<<ui->customplot->selectionRectMode();
  }
  else
  {

    ui->customplot->setSelectionRectMode(QCP::srmNone);
  }
}

void CustomPlotMainWindow::onPlotMouseReleaseEvent(QMouseEvent *event)
{
  qDebug()<<"release";

//  ui->customplot->replot();

//  ui->customplot->setSelectionRectMode(QCP::srmNone);

}

void CustomPlotMainWindow::onPlotPosChanged(const QPointF &point)
{
  ui->label_xy->setText(QString("X:%1,Y:%2").arg(point.x()).arg(point.y()));
}

void CustomPlotMainWindow::onVtagPosChanged(qreal data)
{
  ui->label_vertical->setText(QString("vtag data:%1").arg(data));
}

void CustomPlotMainWindow::onHtagPosChanged(qreal data)
{
  ui->label_horizontal->setText(QString("htag data:%1").arg(data));
}
